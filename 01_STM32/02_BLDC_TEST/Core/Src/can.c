#include "can.h"

int debug_1 = 0;
int debug_2 = 0;

void Can1_Init(void) {
    RCC->AHB1ENR |= (1 << 3);
    RCC->APB1ENR |= (1 << 25);

    GPIOD->MODER &= ~((3 << (0 * 2)) | (3 << (1 * 2)));
    GPIOD->MODER |=  ((2 << (0 * 2)) | (2 << (1 * 2)));

    GPIOD->AFR[0] &= ~((0xF << 0 * 4) | (0xF << 1 * 4));
    GPIOD->AFR[0] |=  ((9 << 0 * 4) | (9 << 1 * 4));

    CAN1->MCR |= (1 << 0);
    while ((CAN1->MSR & (1 << 0)) == 0) {
    }

    CAN1->MCR &= ~(1 << 1);
    CAN1->MCR |= (1 << 6);

    // 비트타이밍 **최중요**
    uint32_t brp = 6;
    uint32_t ts1 = 14;
    uint32_t ts2 = 3;
    uint32_t sjw = 1;

    CAN1->BTR = ((brp - 1) << 0)  |
                ((ts1 - 1) << 16) |
                ((ts2 - 1) << 20) |
                ((sjw - 1) << 24);

    CAN1->MCR &= ~(1 << 0); // INRQ = 0
    while ((CAN1->MSR & (1 << 0)) != 0) {
        // INAK 비트가 0이 될 때까지 대기
    }
}

void Can1_Filter_Config(void) {
    CAN1->FMR |= (1 << 0);


    CAN1->FA1R &= ~(1 << 0);

    CAN1->FM1R &= ~(1 << 0);
    CAN1->FS1R |=  (1 << 0);
    CAN1->FFA1R &= ~(1 << 0);

    CAN1->sFilterRegister[0].FR1 = 0x00000000;
    CAN1->sFilterRegister[0].FR2 = 0x00000000;

    CAN1->FA1R |= (1 << 0);
    CAN1->FMR &= ~(1 << 0);
}

float Can1_Receive_Handler(float current_status) {
    float result_angle = current_status;

    if (CAN1->RF0R & (1 << 3)) {
        CAN1->RF0R |= (1 << 3);
    }

    if ((CAN1->RF0R & (3 << 0)) > 0) {

        uint32_t id = (CAN1->sFIFOMailBox[0].RIR >> 21) & 0x7FF;

        if (id == 0x100) {
            CanData_t rx_data;

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


        CAN1->RF0R |= (1 << 5);
    }

    return result_angle;
}

void Can1_Send_MotorStatus(float current_pos, float current_spd) {
    CanData_t pos, spd;
    pos.f_val = current_pos;
    spd.f_val = current_spd;


    if ((CAN1->TSR & (1 << 26)) != 0) {


        CAN1->sTxMailBox[0].TIR = (0x200 << 21);

        CAN1->sTxMailBox[0].TDTR &= ~(0xF << 0);
        CAN1->sTxMailBox[0].TDTR |= (8 << 0);

        CAN1->sTxMailBox[0].TDLR = (pos.bytes[3] << 24) | (pos.bytes[2] << 16) | (pos.bytes[1] << 8) | pos.bytes[0];
        CAN1->sTxMailBox[0].TDHR = (spd.bytes[3] << 24) | (spd.bytes[2] << 16) | (spd.bytes[1] << 8) | spd.bytes[0];

        CAN1->sTxMailBox[0].TIR |= (1 << 0);
    }
}
