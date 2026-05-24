#ifndef GPWM_H
#define GPWM_H
#include <stdint.h>
#include "gpio.h"
#include "stm32f767xx.h"


void PWM_TIM5_CH1_Init(uint32_t freq);
void PWM_TIM5_CH1_Setduty(float duty_per);
#endif /* __GPWM_H__ */
