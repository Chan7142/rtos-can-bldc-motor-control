#include "can.h"

int debug_1 = 0;
int debug_2 = 0;

void Can1_Init(void) {
    // 1. GPIO 및 CAN1 클록 활성화
    RCC->AHB1ENR |= (1 << 3);   // GPIOD 클록 활성화
    RCC->APB1ENR |= (1 << 25);  // CAN1 클록 활성화

    // 2. GPIOD PIN 0, 1 복합 기능(Alternate Function) 모드 설정
    GPIOD->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2))); // 먼저 00으로 클리어
    GPIOD->MODER |=  ((2 << (0 * 2)) | (2 << (1 * 2)));  // 10: Alternate function mode

    // 3. Alternate Function 매핑 (AF9: CAN1)
    GPIOD->AFR[0] &= ~((0xF << 0 * 4) | (0xF << 1 * 4));
    GPIOD->AFR[0] |=  ((9 << 0 * 4) | (9 << 1 * 4));

    // 4. CAN 초기화 모드 진입
    CAN1->MCR |= (1 << 0);  // INRQ = 1
    while ((CAN1->MSR & (1 << 0)) == 0) {
        // INAK 비트가 1이 될 때까지 대기
    }

    CAN1->MCR &= ~(1 << 1); // SLEEP 해제
    CAN1->MCR |= (1 << 6);  // ABOM (자동 버스 오프 복구 활성화)

    // 5. 비트 타이밍 설정 (BRP, TS1, TS2, SJW 계산)
    uint32_t brp = 6;
    uint32_t ts1 = 14;
    uint32_t ts2 = 3;
    uint32_t sjw = 1;

    CAN1->BTR = ((brp - 1) << 0)  |
                ((ts1 - 1) << 16) |
                ((ts2 - 1) << 20) |
                ((sjw - 1) << 24);

    // 6. 초기화 모드 탈출 및 정상 동작 모드 대기
    CAN1->MCR &= ~(1 << 0); // INRQ = 0
    while ((CAN1->MSR & (1 << 0)) != 0) {
        // INAK 비트가 0이 될 때까지 대기
    }
}

void Can1_Filter_Config(void) {
    CAN1->FMR |= (1 << 0); // FINIT = 1 (필터 초기화 모드 진입)

    // 필터 0번 비활성화 후 설정
    CAN1->FA1R &= ~(1 << 0);

    CAN1->FM1R &= ~(1 << 0);  // 0: 식별자 마스크 모드
    CAN1->FS1R |=  (1 << 0);  // 1: 32비트 스케일 모드
    CAN1->FFA1R &= ~(1 << 0); // 0: FIFO 0 지정

    /**
     * [핵심 변경] 하드코딩 오프셋 주소 계산(+0x240)을 제거하고
     * 정밀 매핑된 새 구조체의 필터 뱅크 배열(sFilterRegister)로 직관적 설정 진행
     */
    CAN1->sFilterRegister[0].FR1 = 0x00000000; // ID 필터 값
    CAN1->sFilterRegister[0].FR2 = 0x00000000; // 마스크 필터 값 (0이면 모든 ID 통과)

    CAN1->FA1R |= (1 << 0);  // 필터 0번 활성화
    CAN1->FMR &= ~(1 << 0);  // FINIT = 0 (필터 초기화 모드 탈출)
}

float Can1_Receive_Handler(float current_status) {
    float result_angle = current_status;

    // 1. FIFO 0 오버런(Overrun) 에러 처리 및 강제 클리어
    if (CAN1->RF0R & (1 << 3)) { // FOVR0 비트 확인
        CAN1->RF0R |= (1 << 3);  // RC_W1(Read/Clear, Write 1)이므로 1을 써서 클리어
    }

    // 2. FIFO 0에 수신 대기 중인 메시지 개수(FMP0) 확인
    if ((CAN1->RF0R & (3 << 0)) > 0) {

        /**
         * [변경] CAN1->RI0R 대신 수신 FIFO 사서함 0 구조체(sFIFOMailBox[0].RIR)에 접근
         * 표준 ID는 비트 [31:21] 영역에서 추출
         */
        uint32_t id = (CAN1->sFIFOMailBox[0].RIR >> 21) & 0x7FF;

        if (id == 0x100) {
            CanData_t rx_data;

            // [변경] CAN1->RDL0R 레지스터 대신 구조체 sFIFOMailBox[0].RDLR 접근
            uint32_t rdl = CAN1->sFIFOMailBox[0].RDLR;
            rx_data.bytes[0] = (rdl >> 0)  & 0xFF;
            rx_data.bytes[1] = (rdl >> 8)  & 0xFF;
            rx_data.bytes[2] = (rdl >> 16) & 0xFF;
            rx_data.bytes[3] = (rdl >> 24) & 0xFF;

            result_angle = rx_data.f_val;

            debug_1++;
        } else {
            debug_2++;
        }

        // 3. 메시지 팝업 완료 후 FIFO 0 수신 버퍼 릴리스 요청
        CAN1->RF0R |= (1 << 5); // RFOM0 = 1 (Release FIFO 0 output mailbox)
    }

    return result_angle;
}

void Can1_Send_MotorStatus(float current_pos, float current_spd) {
    CanData_t pos, spd;
    pos.f_val = current_pos;
    spd.f_val = current_spd;

    // 1. 메일박스 0번이 비어있어 송신 가능한 상태인지 확인 (TME0 비트 체크)
    if ((CAN1->TSR & (1 << 26)) != 0) {

        /**
         * [변경] Mailbox 0번의 개별 제어를 구조체 배열 sTxMailBox[0]으로 처리
         */
        // 2. CAN 표준 ID 0x200 설정 (비트 [31:21] 위치로 시프트)
        CAN1->sTxMailBox[0].TIR = (0x200 << 21);

        // 3. 데이터 길이(DLC) 설정 (위치 4바이트 + 속도 4바이트 = 총 8바이트)
        CAN1->sTxMailBox[0].TDTR &= ~(0xF << 0); // DLC 영역 초기화
        CAN1->sTxMailBox[0].TDTR |= (8 << 0);    // DLC = 8 설정

        // 4. 데이터 적재 (Low 레지스터에 위치 데이터, High 레지스터에 속도 데이터)
        CAN1->sTxMailBox[0].TDLR = (pos.bytes[3] << 24) | (pos.bytes[2] << 16) | (pos.bytes[1] << 8) | pos.bytes[0];
        CAN1->sTxMailBox[0].TDHR = (spd.bytes[3] << 24) | (spd.bytes[2] << 16) | (spd.bytes[1] << 8) | spd.bytes[0];

        // 5. 송신 요청 활성화 (TXRQ 비트 세트)
        CAN1->sTxMailBox[0].TIR |= (1 << 0);
    }
}
