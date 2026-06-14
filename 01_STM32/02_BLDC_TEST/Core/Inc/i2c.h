#ifndef I2C_H
#define I2C_H
#include "dma.h"
#include "gpio.h"
#include "stm32f7xx_it.h"
#include "stm32f767xx.h"

#define I2C1_BASE		0x40005400

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t TIMINGR;
	volatile uint32_t TIMEOUTR;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint32_t PECR;
	volatile uint32_t RXDR;
	volatile uint32_t TXDR;
}I2C_Type;

#define I2C1    ((I2C_Type *)I2C1_BASE)
void I2C1_DMA_Init();

void I2C1_ReadReg_DMA(uint8_t reg_addr, uint8_t *pBuffer, uint16_t size);
float Process_Encoder_Data(void);
#endif
