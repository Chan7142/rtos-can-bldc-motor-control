#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

void Reset_Handler(void);
void Default_Handler(void) { while(1); }

// 인터럽트 핸들러들을 Weak Alias로 설정 (main.c에서 정의하면 덮어씌워짐)
void NMI_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));

void Reset_Handler(void) {
    // [중요] 1. FPU 활성화 (STM32F7 필수)
    // CP10, CP11 권한을 Full Access로 설정하여 FPU를 켭니다.
    *(volatile uint32_t*)0xE000ED88 |= ((3UL << 20) | (3UL << 22));

    // 2. DATA 섹션 복사
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++;

    // 3. BSS 섹션 초기화
    dst = &_sbss;
    while (dst < &_ebss) *dst++ = 0;

    // 4. VTOR 설정 (현재 벡터 테이블의 주소를 CPU에 등록)
    extern void (* const g_pfnVectors[])(void);
    *(volatile uint32_t *)0xE000ED08 = (uint32_t)g_pfnVectors;

    // 5. main 호출
    extern int main(void);
    main();

    while(1);
}

// 벡터 테이블
__attribute__((section(".isr_vector"), used))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))&_estack,   // 0: 스택 포인터
    Reset_Handler,              // 1: 리셋
    NMI_Handler,                // 2: NMI
    HardFault_Handler,          // 3: 하드폴트
    0, 0, 0, 0, 0, 0, 0,        // 4~10: Reserved
    0, 0, 0, 0,                 // 11~14: Reserved
    SysTick_Handler,            // 15: 시스틱

    // 외부 인터럽트 (IRQ 0 ~ 27)
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
    TIM2_IRQHandler             // 44: TIM2 (IRQ 28)
};
