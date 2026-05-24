#ifndef ENCODER_H
#define ENCODER_H
#include "gpio.h"
#include "stm32f767xx.h"
void Encoder_TIM4_Init(void);
uint16_t Get_Encoder_Count(void);
// 회전 방향 확인 (0: Upcount, 1: Downcount)
uint8_t Get_Encoder_Direction(void);

#endif
