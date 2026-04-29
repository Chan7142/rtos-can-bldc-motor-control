#include <gpwm.h>
#include "gpio.h"

//PA0
void PWM_TIM5_CH1_Init(uint32_t freq){
	RCC->AHB1ENR |= (1<<0);
	RCC->APB1ENR |= (1<<3);

	GPIOA->MODER &= ~(3<<(0*2));
	GPIOA->MODER |= (2<<(0*2));

	GPIOA->AFRL &= ~(0xF<<(0*4));
	GPIOA->AFRL |=  (0x02 << (0 * 4));
	GPIOA->OSPEEDR |= (3<<(0*2));

	TIM5->PSC = 0; //분주비0 108Mhz
	TIM5->ARR = (108000000 / freq) - 1;

	TIM5->CCMR1 &= ~(7 << 4); // 기존 4,5,6번 비트 청소
	TIM5->CCMR1 |= (6 << 4);  // PWM Mode 1
	TIM5->CCMR1 |= (1<<3); //preload

	TIM5->CCER |= (1<<0);

	TIM5->CR1 |= (1<<0);
	TIM5->CR1 |= (1<<7);

	TIM5->CCR1 = 0; //초기듀티 0;

}

void PWM_TIM5_CH1_Setduty(float duty_per){
	if(duty_per>100) duty_per = 100;
	if(duty_per<0) duty_per = 0;
	TIM5->CCR1 = (TIM5->ARR)*duty_per/100;
}
