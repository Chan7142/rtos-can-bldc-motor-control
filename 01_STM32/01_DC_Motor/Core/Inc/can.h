#ifndef CAN_H
#define CAN_H
#include <stdint.h>
#include "stm32f7xx_it.h"
#include "stm32f767xx.h"
#define CAN1_BASE		0x40006400
#define CAN2_BASE		0x40006800

typedef struct {
    volatile uint32_t MCR;
    volatile uint32_t MSR;
    volatile uint32_t TSR;
    volatile uint32_t RF0R;
    volatile uint32_t RF1R;
    volatile uint32_t IER;
    volatile uint32_t ESR;
    volatile uint32_t BTR;

    volatile uint32_t RES1[88];

    volatile uint32_t TI0R;
    volatile uint32_t TDT0R;
    volatile uint32_t TDL0R;
    volatile uint32_t TDH0R;

    volatile uint32_t TI1R;
    volatile uint32_t TDT1R;
    volatile uint32_t TDL1R;
    volatile uint32_t TDH1R;

    volatile uint32_t TI2R;
    volatile uint32_t TDT2R;
    volatile uint32_t TDL2R;
    volatile uint32_t TDH2R;

    volatile uint32_t RI0R;
    volatile uint32_t RDT0R;
    volatile uint32_t RDL0R;
    volatile uint32_t RDH0R;

    volatile uint32_t RI1R;
    volatile uint32_t RDT1R;
    volatile uint32_t RDL1R;
    volatile uint32_t RDH1R;

    volatile uint32_t RES2[12];

    volatile uint32_t FMR;
    volatile uint32_t FM1R;
    volatile uint32_t RES3[1];
    volatile uint32_t FS1R;
    volatile uint32_t RES4[1];
    volatile uint32_t FFA1R;
    volatile uint32_t RES5[1];
    volatile uint32_t FA1R;

    volatile uint32_t RES6[8];


    volatile uint32_t FR[56];

}Can_struct;

#define CAN1    ((Can_struct *)CAN1_BASE)
#define CAN2    ((Can_struct *)CAN2_BASE)

void Can1_Init(void);
void Can1_Filter_Config(void);
void Can1_Send_MotorStatus(float current_pos, float current_spd);
float Can1_Receive_Handler(float current_status);

#endif

