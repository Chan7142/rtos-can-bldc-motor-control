#ifndef ADC_H
#define ADC_H
#include "gpio.h"
#include "stm32f7xx_it.h"
#include "stm32f767xx.h"

#define ADC_PERIPH_BASE    0x40012000U
#define ADC1_BASE          (ADC_PERIPH_BASE + 0x000U)
#define ADC2_BASE          (ADC_PERIPH_BASE + 0x100U)
#define ADC3_BASE          (ADC_PERIPH_BASE + 0x200U)
#define ADC_COMMON_BASE    (ADC_PERIPH_BASE + 0x300U) // <-- 추가: 공통 레지스터 주소

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMPR1;
    volatile uint32_t SMPR2;
    volatile uint32_t JOFR1;
    volatile uint32_t JOFR2;
    volatile uint32_t JOFR3;
    volatile uint32_t JOFR4;
    volatile uint32_t HTR;
    volatile uint32_t LTR;
    volatile uint32_t SQR1;
    volatile uint32_t SQR2;
    volatile uint32_t SQR3;
    volatile uint32_t JSQR;
    volatile uint32_t JDR1;
    volatile uint32_t JDR2;
    volatile uint32_t JDR3;
    volatile uint32_t JDR4;
    volatile uint32_t DR;
} ADC_Type;

typedef struct {
    volatile uint32_t CSR;
    volatile uint32_t CCR;
    volatile uint32_t CDR;
} ADC_Common_Type;

// 개별 ADC 제어용
#define ADC1          ((ADC_Type *)ADC1_BASE)
#define ADC2          ((ADC_Type *)ADC2_BASE)
#define ADC3          ((ADC_Type *)ADC3_BASE)

// 공통 레지스터 제어용
#define ADC_COMMON    ((ADC_Common_Type *)ADC_COMMON_BASE)

void ADC_Init(void);

#endif
