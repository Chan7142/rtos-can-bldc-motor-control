#include "timer.h"
#include "rcc.h"

void TIM2_Init(void) {
    RCC->APB1ENR |= (1<<0);


    TIM2->PSC = 108 - 1;
    TIM2->ARR = 10000 - 1;
    TIM2->DIER |= (1 << 0);

    TIM2->CR1 |= (1 << 0);
    *(volatile uint32_t *)0xE000E100 |= (1 << 28);
    TIM2->CR1 |= (1<<0);
}
