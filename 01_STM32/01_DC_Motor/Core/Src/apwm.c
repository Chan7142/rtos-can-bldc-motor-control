#include "apwm.h"
#include "gpio.h"
void PWM_TIM1_Base_Init(uint32_t freq) {
    RCC->AHB1ENR |= (1 << 4);  // GPIOE
    RCC->APB2ENR |= (1 << 0);  // TIM1

    TIM1->PSC = 216 - 1;
    TIM1->ARR = (1000000 / freq) - 1;

    TIM1->CR1 |= (1 << 7);  // ARPE: ARR Preload Enable
    TIM1->BDTR |= (1 << 15); // MOE: Main Output Enable
    TIM1->CR1 |= (1 << 0);  // CEN: Counter Enable
}
//PE9
void PWM_TIM1_CH1_Init(){
	GPIOE->MODER &= ~(3 << 2*9);
	GPIOE->MODER |= (2 << 2*9);
	GPIOE->AFRH &= ~(0xF << 4);
	GPIOE->AFRH |= (1 << 4);

	TIM1->CCMR1 &= ~(0xFF << 0);
	TIM1->CCMR1 |= (6 << 4) | (1 << 3); // PWM Mode 1 + Preload
	TIM1->CCER |= (1 << 0); // CC1E
}
void PWM_TIM1_CH1_Setduty(float duty_per){
	TIM1->CCR1 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
//PE11
void PWM_TIM1_CH2_Init(){
	GPIOE->MODER &= ~(3 << 2*11);
	GPIOE->MODER |= (2 << 2*11);
	GPIOE->AFRH &= ~(0xF << 12);
	GPIOE->AFRH |= (1 << 12);

	TIM1->CCMR1 &= ~(0xFF << 8);
	TIM1->CCMR1 |= (6 << 12) | (1 << 11); // PWM Mode 1 + Preload
	TIM1->CCER |= (1 << 4); // CC2E
}
void PWM_TIM1_CH2_Setduty(float duty_per){
	TIM1->CCR2 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
