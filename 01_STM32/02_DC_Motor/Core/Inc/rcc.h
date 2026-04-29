#ifndef RCC_H
#define RCC_H

#include <stdint.h>

#define RCC_BASE    0x40023800UL

typedef struct {
    volatile uint32_t CR;           // 0x00: 클럭 제어 (HSE, HSI, PLL 켜기)
    volatile uint32_t PLLCFGR;      // 0x04: PLL 설정 (CPU 속도 결정)
    volatile uint32_t CFGR;         // 0x08: 버스 분주비 설정
    volatile uint32_t CIR;          // 0x0C: 클럭 인터럽트
    volatile uint32_t AHB1RSTR;     // 0x10: AHB1 리셋
    volatile uint32_t AHB2RSTR;     // 0x14: AHB2 리셋
    volatile uint32_t AHB3RSTR;     // 0x18: AHB3 리셋
    uint32_t          Reserved0;    // 0x1C: 예약됨
    volatile uint32_t APB1RSTR;     // 0x20: APB1 리셋
    volatile uint32_t APB2RSTR;     // 0x24: APB2 리셋
    uint32_t          Reserved1[2]; // 0x28-0x2C
    volatile uint32_t AHB1ENR;      // 0x30: AHB1 클럭 활성화 (★DMA는 여기!)
    volatile uint32_t AHB2ENR;      // 0x34: AHB2 클럭 활성화
    volatile uint32_t AHB3ENR;      // 0x38: AHB3 클럭 활성화
    uint32_t          Reserved2;    // 0x3C
    volatile uint32_t APB1ENR;      // 0x40: APB1 클럭 활성화 (UART2,3 등)
    volatile uint32_t APB2ENR;      // 0x44: APB2 클럭 활성화 (UART1,6 등)
} RCC_Type;

#define RCC    ((RCC_Type *)RCC_BASE)

void delay_ms(uint32_t ms);
void SystemClock_Config_Max(void);


#define SYSTICK_BASE    0xE000E010UL

typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} My_SysTick_Struct;
extern uint32_t SystemCoreClock;
#define SysTick    ((My_SysTick_Struct*)SYSTICK_BASE)

//PWR

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CSR1;
	volatile uint32_t CR2;
	volatile uint32_t CSR2;
}PWR_Type;
#define PWR_BASE		0x40007000UL
#define PWR		((PWR_Type*)PWR_BASE)

// FLASH
#define FLASH_BASE		0x40023C00UL
typedef struct{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
	volatile uint32_t OPTCR1;
}FLASH_Type;
#define FLASH		((FLASH_Type*)FLASH_BASE)
#endif /*__RCC_H__*/
