#include "encoder.h"


//PD12 PD13
void Encoder_TIM4_Init(void) {
    // 1. 클럭 활성화 (GPIOD, TIM4)
    RCC->AHB1ENR |= (1 << 3);  // GPIOD
    RCC->APB1ENR |= (1 << 2);  // TIM4

    // 2. GPIO 설정 (PD12, PD13 -> AF2)
    GPIOD->MODER   &= ~((3 << 24) | (3 << 26));
    GPIOD->MODER   |=  ((2 << 24) | (2 << 26)); // Alternate Function
    GPIOD->AFRH  &= ~((0xF << 16) | (0xF << 20));
    GPIOD->AFRH  |=  ((2 << 16) | (2 << 20));   // AF2 (TIM4)

    // 3. 엔코더 모드 설정
    TIM4->PSC = 0;              // 프리스케일러는 0 (엔코더 신호 그대로 카운트)
    TIM4->ARR = 0xFFFF;         // 16비트 최대 카운트

    // CCMR1: CC1S=01 (TI1 매핑), CC2S=01 (TI2 매핑)
    TIM4->CCMR1 &= ~((0x3 << 0) | (0x3 << 8));
    TIM4->CCMR1 |=  ((1 << 0) | (1 << 8));

    // CCER: 엣지 설정 (기본값 0: 상승 엣지에서 트리거)
    TIM4->CCER &= ~((1 << 1) | (1 << 5));

    // SMCR: SMS=011 (Encoder Mode 3 - TI1, TI2 둘 다 카운트)
    TIM4->SMCR &= ~(0x7);
    TIM4->SMCR |= 3;

    // 4. 타이머 활성화
    TIM4->CNT = 0;              // 카운터 초기화
    TIM4->CR1 |= (1 << 0);      // CEN: Counter Enable
}

uint16_t Get_Encoder_Count(void) {
    return TIM4->CNT;
}
// 회전 방향 확인 (0: Upcount, 1: Downcount)
uint8_t Get_Encoder_Direction(void) {
    return (TIM4->CR1 >> 4) & 1;
}
