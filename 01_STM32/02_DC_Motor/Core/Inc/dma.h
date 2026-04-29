#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include "spi.h"
#include "rcc.h"


#define DMA1_BASE		0x40026000UL
#define DMA2_BASE		0x40026400UL

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	volatile uint32_t FCR;
}DMA_StreamType;

typedef struct{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;
	DMA_StreamType S[8];
}DMA_Type;

#define DMA1    ((DMA_Type *)DMA1_BASE)
#define DMA2    ((DMA_Type *)DMA2_BASE)

void DMA_Init();
#endif /* __DMA_H__ */
