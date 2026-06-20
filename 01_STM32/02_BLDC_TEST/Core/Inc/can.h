#ifndef CAN_H
#define CAN_H

#include <stdint.h>
#include "stm32f7xx_it.h"
#include "stm32f767xx.h"

// 데이터시트 기준 CAN1, CAN2 기본 주소 정의
#define CAN1_BASE       0x40006400
#define CAN2_BASE       0x40006800

/**
 * @brief CAN 송신 사서함 레지스터 구조체 (Mailbox 0, 1, 2)
 * 오프셋 주소 공간: 사서함당 0x10 바이트 할당
 */
typedef struct {
    volatile uint32_t TIR;      // TX mailbox identifier register
    volatile uint32_t TDTR;     // TX mailbox data length control and time stamp register
    volatile uint32_t TDLR;     // TX mailbox data low register
    volatile uint32_t TDHR;     // TX mailbox data high register
} Can_TxMailbox_TypeDef;

/**
 * @brief CAN 수신 FIFO 사서함 레지스터 구조체 (FIFO 0, 1)
 * 오프셋 주소 공간: 사서함당 0x10 바이트 할당
 */
typedef struct {
    volatile uint32_t RIR;      // RX FIFO mailbox identifier register
    volatile uint32_t RDTR;     // RX FIFO mailbox data length control and time stamp register
    volatile uint32_t RDLR;     // RX FIFO mailbox data low register
    volatile uint32_t RDHR;     // RX FIFO mailbox data high register
} Can_RxMailbox_TypeDef;

/**
 * @brief CAN 필터 뱅크 레지스터 구조체 (Filter 0 ~ 27)
 * 오프셋 주소 공간: 뱅크당 0x08 바이트 할당 (FiR1, FiR2)
 */
typedef struct {
    volatile uint32_t FR1;      // Filter bank register 1
    volatile uint32_t FR2;      // Filter bank register 2
} Can_FilterBank_TypeDef;

/**
 * @brief 데이터시트(RM0410)를 완벽하게 준수한 bxCAN 구조체 매핑
 */
typedef struct {
    volatile uint32_t MCR;      // CAN master control register        (Offset: 0x00)
    volatile uint32_t MSR;      // CAN master status register         (Offset: 0x04)
    volatile uint32_t TSR;      // CAN transmit status register       (Offset: 0x08)
    volatile uint32_t RF0R;     // CAN receive FIFO 0 register        (Offset: 0x0C)
    volatile uint32_t RF1R;     // CAN receive FIFO 1 register        (Offset: 0x10)
    volatile uint32_t IER;      // CAN interrupt enable register      (Offset: 0x14)
    volatile uint32_t ESR;      // CAN error status register          (Offset: 0x18)
    volatile uint32_t BTR;      // CAN bit timing register            (Offset: 0x1C)

    volatile uint32_t RESERVED0[88];

    Can_TxMailbox_TypeDef sTxMailBox[3]; // Mailbox 0, 1, 2 (각 16바이트씩 총 48바이트)

    Can_RxMailbox_TypeDef sFIFOMailBox[2]; // FIFO 0, 1 (각 16바이트씩 총 32바이트)

    volatile uint32_t RESERVED1[12];

    volatile uint32_t FMR;      // CAN filter master register         (Offset: 0x200)
    volatile uint32_t FM1R;     // CAN filter mode register           (Offset: 0x204)
    volatile uint32_t RESERVED2; // Reserved                          (Offset: 0x208)
    volatile uint32_t FS1R;     // CAN filter scale register          (Offset: 0x20C)
    volatile uint32_t RESERVED3; // Reserved                          (Offset: 0x210)
    volatile uint32_t FFA1R;    // CAN filter FIFO assignment register (Offset: 0x214)
    volatile uint32_t RESERVED4; // Reserved                          (Offset: 0x218)
    volatile uint32_t FA1R;     // CAN filter activation register     (Offset: 0x21C)

    // 패딩: 0x220 ~ 0x23F 구간 채움 (0x20 바이트 = 32바이트 = uint32_t 8개)
    volatile uint32_t RESERVED5[8];

    Can_FilterBank_TypeDef sFilterRegister[28]; // Filter Bank 0 ~ 27 (각 8바이트씩 총 224바이트)

} Can_struct;


typedef union {
    float f_val;
    uint8_t bytes[4];
} CanData_t;

// 매크로 정의를 통한 포인터 변환
#define CAN1    ((Can_struct *)CAN1_BASE)
#define CAN2    ((Can_struct *)CAN2_BASE)

// 함수 선언부
void Can1_Init(void);
void Can1_Filter_Config(void);
void Can1_Send_MotorStatus(float current_pos, float current_spd);
float Can1_Receive_Handler(float current_status);

#endif /* CAN_H */
