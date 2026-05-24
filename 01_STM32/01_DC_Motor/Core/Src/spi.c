#include "spi.h"
#include "stm32f7xx_hal.h"

void DMA2_config_SPI1_TX(uint32_t buffer_addr, uint32_t size){
    /* 1. 클럭 활성화 */
    RCC->APB2ENR |= (1 << 12); // SPI1 Clock
    RCC->AHB1ENR |= (1 << 22); // DMA2 Clock

    DMA2->S[3].CR &= ~(1 << 0);           // EN = 0
    while (DMA2->S[3].CR & (1 << 0));      // 하드웨어가 꺼질 때까지 대기

    DMA2->S[3].PAR  = (uint32_t)&(SPI1->DR);
    DMA2->S[3].M0AR = buffer_addr;
    DMA2->S[3].NDTR = size;

    DMA2->S[3].CR = (3 << 25) | (1 << 10) | (1 << 6);


    SPI1->CR1 &= ~(1 << 6); // 일단 SPI 끄기 (설정 변경을 위해)

    // Baud Rate: 108MHz
    SPI1->CR1 &= ~(7 << 3);
    SPI1->CR1 |=  (3 << 3);
    SPI1->CR1 &= ~(1 << 0); // CPHA = 0
    SPI1->CR1 &= ~(1 << 1); // CPOL = 0


    SPI1->CR2 &= ~(0xF << 8);
    SPI1->CR2 |=  (0x7 << 8);

    SPI1->CR2 |= (1 << 12);

    SPI1->CR1 |= (1 << 6) | (1 << 2) | (1 << 8) | (1 << 9);
}

void SPI1_DMA_transfer(uint8_t *addr, uint32_t len) {
	SPI1->CR2 |= (1 << 1);
	// DMA 스트림 비활성화
    DMA2->S[3].CR &= ~(1 << 0);
    while (DMA2->S[3].CR & (1 << 0)); // 완전히 꺼질 때까지 대기

    // 새로운 메모리 주소(M0AR)와 데이터 개수(NDTR) 설정
    DMA2->S[3].M0AR = (uint32_t)addr;
    DMA2->S[3].NDTR = len;

    //  이전 전송 플래그들 모두 청소 (LIFCR)
    DMA2->LIFCR = (0x3D << 22);

    // DMA 스트림 다시 활성화
    DMA2->S[3].CR |= (1 << 0);

    //  전송 완료(TC) 플래그 대기
    while (!(DMA2->LISR & (1 << 27)));

    //  전송 완료 플래그 청소
    DMA2->LIFCR = (1 << 27);
    while (SPI1->SR & (1 << 7)); //대기 **오류 원인**
    SPI1->CR2 &= ~(1 << 1);
}
void SPI1_WriteByte_Polling(uint8_t data) {
    while (!(SPI1->SR & (1 << 1))); // TXE 대기
    *((volatile uint8_t *)&SPI1->DR) = data;
    while (SPI1->SR & (1 << 7));   // BSY 대기 **오류 원인**
}

void CS_ON(void){
    // GPIOD 포트의 14번 핀에 로우(0) 신호를 주어 슬레이브 칩을 활성화(선택)합니다.
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
}

void CS_OFF(void){
    // GPIOD 포트의 14번 핀에 하이(1) 신호를 주어 슬레이브 칩을 비활성화(해제)합니다.
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
}

void SPI_GPIO_Init(void) {
    // 1. 사용할 모든 GPIO 포트(GPIOA, GPIOD, GPIOF)의 클럭 활성화
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    // 2. GPIO 초기화 설정을 위한 구조체 변수 선언 (단 한 번만 선언해서 재사용)
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ====================================================================
    // [단독 설정 1] GPIOD - 14번 핀 (CS 핀: 일반 출력 모드)
    // ====================================================================
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;       // 일반 출력(Push-Pull)
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 최고속 설정
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    // ====================================================================
    // [단독 설정 2] GPIOF - 12번, 13번 핀 (A0 / RESET 핀: 일반 출력 모드)
    // ====================================================================
    // (12번 핀과 13번 핀 모두 출력 모드로 같으므로 비트 기호 '|' 로 묶어서 한 번에 세팅합니다)
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;       // 일반 출력(Push-Pull)
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 최고속 설정
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    // ====================================================================
    // [단독 설정 3] GPIOA - 5번, 7번 핀 (SPI1 SCK / MOSI 핀: 대체 기능 모드)
    // ====================================================================
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           // 대체 기능(Alternate Function) 푸시풀
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // 고속 SPI 통신을 위한 최고속 설정
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;        // 두 핀의 기능을 AF5(SPI1)로 지정
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


