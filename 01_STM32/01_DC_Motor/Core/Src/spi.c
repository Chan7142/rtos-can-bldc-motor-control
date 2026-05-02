#include "spi.h"

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

void CS_ON(){
	GPIO_Write_Pin(GPIOD, 14, 0);
}
void CS_OFF(){
	GPIO_Write_Pin(GPIOD, 14, 1);
}

void SPI_GPIO_Init(){
	GPIO_Clock_Enable(GPIOD);
	GPIO_pin_Mode(GPIOD, 14, 1);
	GPIO_Speed_Set(GPIOD, 14, 3);
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOF);
	GPIO_pin_Mode(GPIOF, 13, 1);
	GPIO_Speed_Set(GPIOF, 13, 3);

	GPIO_pin_Mode(GPIOA, 5, 2); // PA5 -> AF Mode
	GPIO_pin_Mode(GPIOA, 7, 2); // PA7 -> AF M
	GPIO_Speed_Set(GPIOA, 5, 3);
	GPIO_Speed_Set(GPIOA, 7, 3);

	GPIOA->AFRL &= ~(0xF << (5 * 4)); // 초기화
	GPIOA->AFRL |=  (0x5 << (5 * 4)); // AF5(SPI1) 주입
	GPIOA->AFRL &= ~(0xF << (7 * 4)); // 초기화
	GPIOA->AFRL |=  (0x5 << (7 * 4)); // AF5(SPI1) 주입
}


