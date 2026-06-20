#ifndef SPI_H
#define SPI_H

#define SPI1_BASE    0x40013000UL
#include "dma.h"
#include "gpio.h"

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
} MY_SPI_TypeDef;

#define SPI1    ((MY_SPI_TypeDef *)SPI1_BASE)

void DMA2_config_SPI1_TX(uint32_t buffer_addr, uint32_t size);

void SPI1_DMA_transfer(uint8_t *addr, uint32_t len);
void SPI1_WriteByte_Polling(uint8_t data);

void CS_ON();
void CS_OFF();

void SPI_GPIO_Init();

#endif /* __SPI_H__ */
