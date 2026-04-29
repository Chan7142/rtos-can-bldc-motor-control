#include "rcc.h"
//uint32_t SystemCoreClock = 216000000;
void delay_ms(uint32_t ms) {
    if (ms == 0) return;

    // 1. SysTick 설정: 1ms 주기로 설정
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;
    SysTick->VAL = 0; // 현재 값 초기화
    SysTick->CTRL = (1 << 2) | (1 << 0); // Processor Clock 사용, 타이머 활성화

    for (uint32_t i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & (1 << 16)));
    }

    // 3. 종료 후 타이머 끄기
    SysTick->CTRL = 0;
}
void SystemClock_Config_Max(void) {

	uint32_t SystemCoreClock = 216000000;
    /* 2. HSE (External Crystal) 활성화 */
    RCC->CR |= (1 << 16); // HSEON
    while (!(RCC->CR & (1 << 17))); // HSERDY 대기

    /* 3. 전원 인터페이스 클럭 활성화 및 VOS 설정 */
    RCC->APB1ENR |= (1 << 28); // PWREN
    (void)RCC->APB1ENR; // 클럭 안정화를 위한 더미 읽기

    //VOS Scale 1 설정 최고성능
    PWR->CR1 |= (3 << 14);

    // VOSRDY 대기 (멈춤 방지를 위한 타이아웃 처리)
    uint32_t timeout = 0xFFFF;
    while (!(PWR->CR1 & (1 << 14)) && timeout--);

    ///* 4. Over-drive 모드 활성화 (216MHz 필수 시퀀스) */
    PWR->CR1 |= (1 << 16); // ODEN (Over-drive Enable)
    while (!(PWR->CSR1 & (1 << 16))); // ODRDY 대기

    PWR->CR1 |= (1 << 17); // ODSWEN (Over-drive Switching Enable)
    while (!(PWR->CSR1 & (1 << 17))); // ODSWRDY 대기

    /* 5. Flash ACR 설정 (216MHz에서는 반드시 7 Wait States 필요) */
    // ART Accelerator 활성화 (ICEN, DCEN, PRFTEN) + Latency 7WS
    FLASH->ACR |= (1 << 11);
    FLASH->ACR = (1 << 9)| (1 << 8) | (7 << 0);

    RCC->PLLCFGR = (4 << 0) | (216 << 6) | (0 << 16) | (1 << 22);

    /* 7. PLL 활성화 */
    RCC->CR |= (1 << 24); // PLLON
    while (!(RCC->CR & (1 << 25))); // PLLRDY 대기

    RCC->CFGR = (0 << 4) | (5 << 10) | (4 << 13);

    /* 9. 시스템 클럭 전환 (SYSCLK Source = PLL) */
    RCC->CFGR |= (2 << 0); // SW = PLL
    while ((RCC->CFGR & (0x0C)) != (0x08)); // SWS가 PLL(10)인지 확인
}
