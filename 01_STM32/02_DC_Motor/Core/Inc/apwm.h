#ifndef APWM_H
#define APWM_H
#include <stdint.h>
//TIM1 TIM8 register
#define TIM1_BASE		0x40010000
#define TIM8_BASE		0x40010400

typedef struct {
    volatile uint32_t CR1;    // 0x00
    volatile uint32_t CR2;    // 0x04
    volatile uint32_t SMCR;   // 0x08
    volatile uint32_t DIER;   // 0x0C
    volatile uint32_t SR;     // 0x10
    volatile uint32_t EGR;    // 0x14
    volatile uint32_t CCMR1;  // 0x18
    volatile uint32_t CCMR2;  // 0x1C
    volatile uint32_t CCER;   // 0x20
    volatile uint32_t CNT;    // 0x24
    volatile uint32_t PSC;    // 0x28
    volatile uint32_t ARR;    // 0x2C
    volatile uint32_t RCR;    // 0x30
    volatile uint32_t CCR1;   // 0x34
    volatile uint32_t CCR2;   // 0x38
    volatile uint32_t CCR3;   // 0x3C
    volatile uint32_t CCR4;   // 0x40
    volatile uint32_t BDTR;   // 0x44
    volatile uint32_t DCR;    // 0x48
    volatile uint32_t DMAR;   // 0x4C
    volatile uint32_t OR;     // 0x50 *주의*
    volatile uint32_t CCMR3;  // 0x54
    volatile uint32_t CCR5;   // 0x58
    volatile uint32_t CCR6;   // 0x5C
    volatile uint32_t AF1;    // 0x60
    volatile uint32_t AF2;    // 0x64
} TIM_ADV_Type;

#define TIM1		((TIM_ADV_Type*)TIM1_BASE)
#define TIM8		((TIM_ADV_Type*)TIM8_BASE)

//PE9
void PWM_TIM1_CH1_Init();
void PWM_TIM1_CH1_Setduty(float duty_per);
//PE11
void PWM_TIM1_CH2_Init();
void PWM_TIM1_CH2_Setduty(float duty_per);
void PWM_TIM1_Base_Init(uint32_t freq);




#endif /* __APWM_H__ */
