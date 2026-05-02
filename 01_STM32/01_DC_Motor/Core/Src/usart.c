#include "usart.h"
#include "rcc.h"
#include "gpio.h"
#include "dma.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void Usart3_TX_Init(uint32_t baudrate){
	RCC->AHB1ENR |= (1 << 3);      // GPIOD 활성화
	RCC->APB1ENR |= (1 << 18);      // USART3 활성화

	GPIOD->MODER &= ~((3 << 16) | (3 << 18)); // PD8 PD9
	GPIOD->MODER |=  ((2 << 16) | (2 << 18)); // AF 모드

	GPIOD->AFRH |= (7 << 0) | (7 << 4);

	//baud rate 설정
	uint32_t brr_val;
	brr_val = (54000000 + (baudrate / 2)) / baudrate;
	USART3->BRR = (uint16_t)brr_val;

	USART3->CR1 = (1 << 0) | (1 << 3) | (1 << 2);
	USART3->CR3 |= (1 << 7); //DMA 허용
}

void DMA_USART3_Init(){
	DMA1->S[3].CR &= ~1UL; //초기화
	while(DMA1->S[3].CR & 1UL); //대기
	DMA1->LIFCR |= (0x3D << 22); //인터럽트 플래그 클리어


	DMA1->S[3].PAR = (uint32_t)&USART3->TDR; //주소선택 데이터 송신
	// 채널4, 우선순위 중간,MINC ->1, Memory-to-Peripheral
	DMA1->S[3].CR = (4 << 25) | (1 << 16) | (1 << 10) | (1 << 6);
}
void USART3_DMA_Send(uint8_t *data, uint16_t size) {
    // 전송 중인지 확인 후 중지
    DMA1->S[3].CR &= ~1UL;
    while(DMA1->S[3].CR & 1UL);

    // 전송 정보 업데이트
    DMA1->S[3].M0AR = (uint32_t)data;   // 전송할 버퍼 주소
    DMA1->S[3].NDTR = size;            // 데이터 개수

    // 인터럽트 플래그 다시 클리어
    DMA1->LIFCR |= (0x3D << 22);

    // DMA 활성화 (전송 시작)
    DMA1->S[3].CR |= 1UL;
}
int _write(int file, char *ptr, int len) {
    USART3_DMA_Send((uint8_t *)ptr, (uint16_t)len);
    while(DMA1->S[3].CR & 1UL);
    return len;
}
