#include "spi.h"

void DMA2_config_SPI1_TX(uint32_t buffer_addr, uint32_t size){
    /* 1. 클럭 활성화 */
    RCC->APB2ENR |= (1 << 12); // SPI1 Clock
    RCC->AHB1ENR |= (1 << 22); // DMA2 Clock

    /* 2. DMA 스트림 정지 및 완전 종료 대기 */
    DMA2->S[3].CR &= ~(1 << 0);           // EN = 0
    while (DMA2->S[3].CR & (1 << 0));      // 하드웨어가 꺼질 때까지 대기

    /* 3. 레지스터 초기 설정 (|= 대신 = 사용 권장) */
    DMA2->S[3].PAR  = (uint32_t)&(SPI1->DR);
    DMA2->S[3].M0AR = buffer_addr;
    DMA2->S[3].NDTR = size;

    // CR 설정 초기화 후 필요한 것만 셋업
    // Channel 3(3<<25), Memory Inc(1<<10), DIR: Mem-to-Peri(1<<6)
    DMA2->S[3].CR = (3 << 25) | (1 << 10) | (1 << 6);

    /* 4. SPI1 상세 설정 (STM32F7 특화) */
    SPI1->CR1 &= ~(1 << 6); // 일단 SPI 끄기 (설정 변경을 위해)

    // Baud Rate: 108MHz / 16 = 6.75MHz (BR[2:0] = 011)
    SPI1->CR1 &= ~(7 << 3);
    SPI1->CR1 |=  (3 << 3);
    SPI1->CR1 &= ~(1 << 0); // CPHA = 0
    SPI1->CR1 &= ~(1 << 1); // CPOL = 0

    // 3. STM32F7 핵심: Data Size 8-bit 설정 (DS[3:0] = 0111)
    SPI1->CR2 &= ~(0xF << 8);
    SPI1->CR2 |=  (0x7 << 8);

    // 4. STM32F7 핵심: FIFO Threshold 8-bit 설정 (FRXTH = 1)
    // 이 설정이 없으면 8비트 전송이 꼬입니다.
    SPI1->CR2 |= (1 << 12);
    //활성화
    //SPI1->CR2 |= (1 << 1);
    SPI1->CR1 |= (1 << 6) | (1 << 2) | (1 << 8) | (1 << 9);
}

void SPI1_DMA_transfer(uint8_t *addr, uint32_t len) {
	SPI1->CR2 |= (1 << 1);
	// 1. DMA 스트림 비활성화 (설정 변경을 위해 필수)
    DMA2->S[3].CR &= ~(1 << 0);
    while (DMA2->S[3].CR & (1 << 0)); // 완전히 꺼질 때까지 대기

    // 2. 새로운 메모리 주소(M0AR)와 데이터 개수(NDTR) 설정
    DMA2->S[3].M0AR = (uint32_t)addr;
    DMA2->S[3].NDTR = len;

    // 3. 이전 전송 플래그들 모두 청소 (LIFCR)
    // Stream 3의 플래그 위치: FEIF3, DMEIF3, TEIF3, HTIF3, TCIF3
    DMA2->LIFCR = (0x3D << 22);

    // 4. DMA 스트림 다시 활성화
    DMA2->S[3].CR |= (1 << 0);

    // 5. 전송 완료(TC) 플래그 대기
    while (!(DMA2->LISR & (1 << 27)));

    // 6. 전송 완료 플래그 청소
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


