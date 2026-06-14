#include "stm32f7xx_it.h"
#include "stm32f7xx_hal.h"
#include "apwm.h"
#include "gpio.h"


void PWM_TIM1_Base_Init(uint32_t freq) {
    RCC->AHB1ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);

    TIM1->PSC = 108 - 1;
    TIM1->ARR = (1000000 / freq)  - 1;

    TIM1->CR1 |= (1 << 7);

    TIM1->CR1 &= ~(3 << 5);
    //TIM1->CR1 |= (1 << 5);
}
//PE9 PE8
void PWM_TIM1_CH1_Init(){
	//GPIOE->MODER &= ~((3 << 2*8) | (3 << 2*9));
	//GPIOE->MODER |=  ((2 << 2*8) | (2 << 2*9));
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	TIM1->CCMR1 &= ~(7 << 4);
	TIM1->CCMR1 |= (6 << 4);    // PWM Mode1
	TIM1->CCMR1 |= (1 << 3);

	TIM1->BDTR = (1 << 11) | (0x9B << 0);

	TIM1->CCER &= ~((1 << 1) | (1 << 3)); // 극성은 Active High
	TIM1->CCER |= (1 << 0) | (1 << 2);

	TIM1->EGR |= (1 << 0);
	TIM1->BDTR |= (1 << 15);
	   //
	 //
	TIM1->CR1 |= (1 << 0);   //
}
void PWM_TIM1_CH1_Setduty(float duty_per){
	TIM1->CCR1 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
//PE11 PE10
void PWM_TIM1_CH2_Init(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    TIM1->CCMR1 &= ~(7 << 12);
    TIM1->CCMR1 |= (6 << 12);
    TIM1->CCMR1 |= (1 << 11);

    TIM1->CCER &= ~((1 << 5) | (1 << 7));
    TIM1->CCER |= (1 << 4) | (1 << 6);

    TIM1->EGR |= (1 << 0);
    TIM1->BDTR |= (1 << 15);

    TIM1->CR1 |= (1 << 0);
}

void PWM_TIM1_CH2_Setduty(float duty_per){
    TIM1->CCR2 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
// PE13, PE12
void PWM_TIM1_CH3_Init(){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    TIM1->CCMR2 &= ~(7 << 4);
    TIM1->CCMR2 |= (6 << 4);
    TIM1->CCMR2 |= (1 << 3);

    TIM1->CCER &= ~((1 << 9) | (1 << 11));
    TIM1->CCER |= (1 << 8) | (1 << 10);

    TIM1->EGR |= (1 << 0);
    TIM1->BDTR |= (1 << 15);

    TIM1->CR1 |= (1 << 0);
}

void PWM_TIM1_CH3_Setduty(float duty_per){
    // Channel 3 비교 레지스터인 CCR3에 값 대입
    TIM1->CCR3 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
