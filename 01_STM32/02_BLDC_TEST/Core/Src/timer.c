#include "timer.h"
#include "stm32f7xx_it.h"
#include "stm32f767xx.h"

void TIM2_Init(void) {
    RCC->APB1ENR |= (1<<0);


    TIM2->PSC = 108 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->DIER |= (1 << 0);

    TIM2->CR1 |= (1 << 0);
    *(volatile uint8_t *)(0xE000E400 + 28) = (7 << 4); //우선순위
    *(volatile uint32_t *)0xE000E100 |= (1 << 28);
    TIM2->CR1 |= (1<<0);
}
