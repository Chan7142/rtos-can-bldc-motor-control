#ifndef USART_H
#define USART_H
#include <stdint.h>
#define USART1_BASE		0x40011000
#define USART2_BASE		0x40004400
#define USART3_BASE		0x40004800
#define UART4_BASE		0x40004C00
#define UART5_BASE		0x40005000
#define USART6_BASE		0x40011400

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t BRR;
	volatile uint32_t GTPR;
	volatile uint32_t RTOR;
	volatile uint32_t RQR;
	volatile uint32_t ISR;
	volatile uint32_t ICR;
	volatile uint32_t RDR;
	volatile uint32_t TDR;
}Usart_Type;

#define USART1		((Usart_Type*)USART1_BASE)
#define USART2		((Usart_Type*)USART2_BASE)
#define USART3		((Usart_Type*)USART3_BASE)
#define UART4		((Usart_Type*)UART4_BASE)
#define UART5		((Usart_Type*)UART5_BASE)
void Usart3_TX_Init(uint32_t baudrate);

void DMA_USART3_Init();
void USART3_DMA_Send(uint8_t *data, uint16_t size);
#endif
