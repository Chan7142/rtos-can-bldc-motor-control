#ifndef SPI_H
#define SPI_H

#define SPI1_BASE    0x40013000UL
#include "dma.h"
#include "gpio.h"

typedef struct {
    volatile uint32_t CR1;    // 0x00: 제어 레지스터 1
    volatile uint32_t CR2;    // 0x04: 제어 레지스터 2 (DMA 요청 비트가 여기 있음)
    volatile uint32_t SR;     // 0x08: 상태 레지스터
    volatile uint32_t DR;     // 0x0C: 데이터 레지스터 (여기에 쓰면 MOSI로 나감)
    volatile uint32_t CRCPR;  // 0x10: CRC 다항식
    volatile uint32_t RXCRCR; // 0x14: RX CRC
    volatile uint32_t TXCRCR; // 0x18: TX CRC
} MY_SPI_TypeDef;

#define SPI1    ((MY_SPI_TypeDef *)SPI1_BASE)

void DMA2_config_SPI1_TX(uint32_t buffer_addr, uint32_t size);

void SPI1_DMA_transfer(uint8_t *addr, uint32_t len);
void SPI1_WriteByte_Polling(uint8_t data);

void CS_ON();
void CS_OFF();

void SPI_GPIO_Init();

#endif /* __SPI_H__ */
