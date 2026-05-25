#include "can.h"

void Can1_Init(){
	RCC->AHB1ENR |= (1<<3);
	RCC->APB1ENR |= (1<<25);

	GPIOD->MODER |= (2<<0*2);
	GPIOD->MODER |= (2<<1*2);

	GPIOD->AFR[0] &= ~((0xF << 0*4) | (0xF << 1*4));
	GPIOD->AFR[0] |=  ((9 << 0*4) | (9 << 1*4));

	CAN1->MCR |= (1 << 0);
	while ((CAN1->MSR & (1 << 0)) == 0) {
	}
	CAN1->MCR &= ~(1 << 1); //슬립해제
	CAN1->MCR |= (1 << 6);

	uint32_t brp = 3;
	uint32_t ts1 = 14;
	uint32_t ts2 = 3;
	uint32_t sjw = 1;

	CAN1->BTR = ((brp - 1) << 0)  |
	            ((ts1 - 1) << 16) |
	            ((ts2 - 1) << 20) |
	            ((sjw - 1) << 24);

	CAN1->MCR &= ~(1 << 0); //초기화 탈출
	while ((CAN1->MSR & (1 << 0)) != 0) { //대기
	    }

}

void Can1_Filter_Config(void) {
    // 필터 초기화 모드 진입
    CAN1->FMR |= (1 << 0); // FINIT = 1

    // 필터 0번 사용, 식별자 마스크 모드(Id/Mask) 설정
    CAN1->FM1R &= ~(1 << 0); // FBM0 = 0 (Mask 모드)
    CAN1->FS1R |=  (1 << 0); // FSC0 = 1 (32비트 스케일)
    CAN1->FFA1R &= ~(1 << 0); // FFA0 = 0 (수신 데이터를 FIFO 0으로 할당)

    volatile uint32_t *filter_base = (volatile uint32_t *)((uint32_t)CAN1 + 0x240);
    filter_base[0] = 0x00000000; // Filter 0 R1 (FR1)
    filter_base[1] = 0x00000000;
    // 필터 활성화 및 초기화 모드 탈출
    CAN1->FA1R |= (1 << 0);  // FACT0 = 1 (필터 0번 활성화)
    CAN1->FMR &= ~(1 << 0);  // FINIT = 0
}

typedef union {
    float f_val;
    uint8_t bytes[4];
} CanData_t;


float Can1_Receive_Handler(float current_status) {
    // 새로운 데이터가 없거나 ID가 다르면 이 값이 그대로 리턴.
    float result_angle = current_status;

    // FIFO 0에 수신된 메시지 개수 확인 (FMP0 비트 체크)
    if ((CAN1->RF0R & (3 << 0)) > 0) {

        // 1. CAN ID 확인 (표준 ID는 STID[10:0] 영역인 비트 21~31에 위치함)
        uint32_t id = (CAN1->RI0R >> 21) & 0x7FF;

        if (id == 0x100) { // PC 지령 ID 일치 여부 확인
            CanData_t rx_data; // 변수 선언 위치는 유지하되, 값을 내부에서 바로 저장

            // Low 데이터 레지스터(0~3바이트)에서 값을 순서대로 가져옴 (Little Endian 기준)
            uint32_t rdl = CAN1->RDL0R;
            rx_data.bytes[0] = (rdl >> 0)  & 0xFF;
            rx_data.bytes[1] = (rdl >> 8)  & 0xFF;
            rx_data.bytes[2] = (rdl >> 16) & 0xFF;
            rx_data.bytes[3] = (rdl >> 24) & 0xFF;

            // 정상적으로 수신된 최종 float 각도 데이터를 반환용 변수에 대입
            result_angle = rx_data.f_val;
        }

        // FIFO 0 방출 요청 (★중요: ID가 다르더라도 FIFO에 쌓인 메시지는 방출해야 다음 메시지가 들어옴)
        CAN1->RF0R |= (1 << 5); // RFOM0 = 1
    }

    // 모든 경로에서 안전하게 값이 반환.
    return result_angle;
}

void Can1_Send_MotorStatus(float current_pos, float current_spd) {
    CanData_t pos, spd;
    pos.f_val = current_pos;
    spd.f_val = current_spd;

    //  빈 송신 메일박스가 있는지 확인 (TSR 레지스터의 TME 비트들 체크)
    if ((CAN1->TSR & (1 << 26)) != 0) {

        // 2. CAN ID 설정 (표준 ID 0x200 대입 후 21비트 시프트)
        CAN1->TI0R = (0x200 << 21);

        // 3. 데이터 길이 설정 (현재 위치 4바이트 + 속도 4바이트 = 총 8바이트)
        CAN1->TDT0R &= ~(0xF << 0); // DLC 비트 초기화
        CAN1->TDT0R |= (8 << 0);    // DLC = 8

        // 4. 데이터 적재
        // Low 레지스터에 현재 위치 4바이트 배치
        CAN1->TDL0R = (pos.bytes[3] << 24) | (pos.bytes[2] << 16) | (pos.bytes[1] << 8) | pos.bytes[0];
        // High 레지스터에 현재 속도 4바이트 배치
        CAN1->TDH0R = (spd.bytes[3] << 24) | (spd.bytes[2] << 16) | (spd.bytes[1] << 8) | spd.bytes[0];

        // 5. 송신 요청 (TXRQ 비트 세트)
        CAN1->TI0R |= (1 << 0);
    }
}
