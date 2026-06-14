#include "encoder.h"
#include "stm32f7xx_hal.h"


//PD12 PD13
void Encoder_TIM4_Init(void) {
    // 1. 클럭 활성화 (GPIOD, TIM4)
    RCC->AHB1ENR |= (1 << 3);  // GPIOD
    RCC->APB1ENR |= (1 << 2);  // TIM4

    // 2. GPIO 설정 (PD12, PD13 -> AF2)
    GPIOD->MODER   &= ~((3 << 24) | (3 << 26));
    GPIOD->MODER   |=  ((2 << 24) | (2 << 26)); // Alternate Function
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 2. PD12, PD13 핀 지정
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;

    // 3. 모드를 Alternate Function(대체 기능) 푸시풀로 설정
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;

    // 4. 풀업/풀다운은 끈 상태 유지 (레지스터 기본값)
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    // 5. 핀 출력 속도 설정 (엔코더 신호를 받아야 하므로 High 속도 추천)
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    // 6. [★질문하신 AFRH 레지스터 대응 핵심 코드★]
    // 두 핀의 대체 기능을 AF2(TIM4)로 지정합니다.
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;

    // 7. GPIOD 포트에 위 설정값들을 최종 주입 (내부에서 AFRH 비트 연산이 자동 수행됨)
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
