#include "fonts.h"
#include "main.h"
#include "string.h"
#include "gpwm.h"
#include "apwm.h"
#include <stdint.h>
#include <stdio.h>
#include "rcc.h"
#include "encoder.h"
#include "usart.h"
const uint32_t ENCODER_RESOLUTION = 1320;
void SystemClock_Config_Max(void);
uint32_t current_cnt = 0;
uint32_t gCount = 0;
uint32_t T_s = 0;
float u_k = 0;
float d1 = 0;
float d2 = 0;
float D = 0;
float pi = 3.141592;
float speed_rad = 0;
float speed_rpm = 0;
float Ts = 0.01;
uint32_t debug1 = 0;
uint32_t debug2 = 0;
uint32_t cnt_cur = 0;
uint32_t cnt_prev = 0;
void motor_input(float input){
	D = input / 12;
	if(D > 1) D = 1;
	else if(D < -1) D = -1;
	d1 = (1+D)/2;
	d2 = (1-D)/2;
	PWM_TIM1_CH1_Setduty(d1);
	PWM_TIM1_CH2_Setduty(d2);
}

float get_motor_speed_rpm(){
	cnt_cur = Get_Encoder_Count();
	int16_t delta_cnt = (int16_t)(cnt_cur - cnt_prev);
	if (delta_cnt < -32768) {
	    delta_cnt += 65536;
	}
	else if (delta_cnt > 32768) {
	    delta_cnt -= 65536;
	}
	cnt_prev = cnt_cur;
	return ((float)delta_cnt/ENCODER_RESOLUTION)* 60 / Ts;
}

int main(void)
{

	SystemClock_Config_Max();

	SPI_GPIO_Init();
	DMA_Init();
	uint8_t test_data[4] = {0xAA, 0xBB, 0xCC, 0xDD};
	DMA2_config_SPI1_TX((uint32_t)test_data, 4);

	ST7735_Init();              // 1. 초기화 (이전 단계에서 만든 함수)
	ST7735_FillScreen(0x0000);  // 2. 검정색으로 배경 채우기
	ST7735_WriteString(10, 50, "Hello World", Font_7x10, 0xFFFF, 0x0000);
	PWM_TIM5_CH1_Init(1000);
	PWM_TIM5_CH1_Setduty(80); //80% pwm duty
	PWM_TIM1_Base_Init(1000);
	PWM_TIM1_CH1_Init();
	PWM_TIM1_CH2_Init();
	Encoder_TIM4_Init();
	Usart3_TX_Init(115200);
	DMA_USART3_Init();


	//테스트용
	GPIO_pin_Mode(GPIOE, 15, 1);
  while (1)
  {
	  motor_input(0);
	  speed_rpm = get_motor_speed_rpm();
	  printf("%.2f\n", speed_rpm);
	  delay_ms(10);
	  gCount++;
  }

}

