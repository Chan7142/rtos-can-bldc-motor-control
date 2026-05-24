#include "stm32f7xx_it.h"
#include "stm32f7xx_hal.h"
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
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// 2. 대상 핀 지정 (9번 핀)
	GPIO_InitStruct.Pin = GPIO_PIN_9;

	// 3. 모드를 Alternate Function(대체 기능) 푸시풀로 설정
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;

	// 4. 내부 풀업/풀다운 저항 사용 안 함
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	// 5. 타이머 PWM 출력을 안정적으로 뽑아내기 위해 고속(High) 설정
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	// 6. [★질문하신 AFRH 레지스터 대응 핵심 코드★]
	// 9번 핀의 기능을 AF1(TIM1) 기능으로 지정합니다.
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

	// 7. GPIOE 포트에 설정값을 최종 주입
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

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
	/* PE11 핀을 TIM1_CH2 대체 기능으로 매핑하는 코드 */

	// 1. GPIO 초기화 구조체 변수 선언
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// 2. 대상 핀 지정 (11번 핀)
	GPIO_InitStruct.Pin = GPIO_PIN_11;

	// 3. 모드를 Alternate Function(대체 기능) 푸시풀로 설정
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;

	// 4. 내부 풀업/풀다운 저항 사용 안 함
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	// 5. PWM 출력 신호를 안정적으로 뽑아내기 위해 고속(High) 설정
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	// 6. [★질문하신 AFRH 레지스터 대응 핵심 코드★]
	// 11번 핀의 기능을 AF1(TIM1) 기능으로 지정합니다.
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

	// 7. GPIOE 포트에 설정값을 최종 주입
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	TIM1->CCMR1 &= ~(0xFF << 8);
	TIM1->CCMR1 |= (6 << 12) | (1 << 11); // PWM Mode 1 + Preload
	TIM1->CCER |= (1 << 4); // CC2E
}
void PWM_TIM1_CH2_Setduty(float duty_per){
	TIM1->CCR2 = (uint32_t)((float)(TIM1->ARR + 1) * (duty_per));
}
