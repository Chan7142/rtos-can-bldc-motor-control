#include "dma.h"


uint32_t src_data[4] = {0x12345678, 0xABCDEF01, 0x98765432, 0xDEADBEEF};
uint32_t dest_data[4] = {0,};

void DMA_Init(){
	RCC->AHB1ENR |= (1 << 21); //DMA1번 켜기
	RCC->AHB1ENR |= (1 << 22); //DMA2번 켜기
	uint32_t dummy = RCC->AHB1ENR;
	(void)dummy;

	//시작
	//RCC->CR |= (1<<16);
	//while(!(RCC->CR&(1<<17)));
}




