/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "cmsis_os.h"
#include "fonts.h"
#include "main.h"
#include "string.h"
#include "gpwm.h"
#include "apwm.h"
#include <stdint.h>
#include <stdio.h>
#include <Subsystem.h>
#include <math.h>
#include "stm32f7xx_it.h"
#include "encoder.h"
#include "usart.h"
#include "timer.h"
#include "can.h"
#include "i2c.h"
#include "adc.h"
extern volatile uint32_t msTicks = 0;
const uint32_t ENCODER_RESOLUTION = 1320;
void SystemClock_Config_Max(void);
uint32_t current_cnt = 0;
float gCount = 0;
float mCount = 0;
float time = 0;
float u_k = 0;
float d1 = 0;
float d2 = 0;
float D = 0;
float pi = 3.14159265;
float speed_rad = 0;
float speed_rpm = 0;
float theta_rad = 0;
float theta_degree = 0;
float desired_theta = 0;
float Ts = 0.001;
float Tc = 0.0002;
const float pole_pairs = 7;
float angle_e = 0;
float I_a = 0;
float I_b = 0;
float I_c = 0;
float Rs = 2.55;
float Ls = 0.00086;
float Wc = 0;
float Kpc = 0;
float Kic = 0;
float V_ref = 0;
float Iq_ref = 0;
float Id = 0;
float Iq = 0;
char buf[32];
uint32_t debug1 = 0;
uint32_t debug2 = 0;
uint32_t cnt_cur = 0;
uint32_t cnt_prev = 0;
static float desired_theta_deg = 0.0f;
float spi_count = 0;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x2007c000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x2007c0a0
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x2007c000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x2007c0a0))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __GNUC__ ) /* GNU Compiler */

ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection")));   /* Ethernet Tx DMA Descriptors */
#endif

ETH_TxPacketConfig TxConfig;

ETH_HandleTypeDef heth;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for motorControl */
osThreadId_t motorControlHandle;
const osThreadAttr_t motorControl_attributes = {
  .name = "motorControl",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for SPI */
osThreadId_t SPIHandle;
const osThreadAttr_t SPI_attributes = {
  .name = "SPI",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CAN */
osThreadId_t CANHandle;
const osThreadAttr_t CAN_attributes = {
  .name = "CAN",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UART */
osThreadId_t UARTHandle;
const osThreadAttr_t UART_attributes = {
  .name = "UART",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
void StartDefaultTask(void *argument);
void mControl(void *argument);
void SPI_T(void *argument);
void CAN_T(void *argument);
void UART_T(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPIOG_Init();
  MX_ETH_Init();
  MX_USB_OTG_FS_PCD_Init();
  /* USER CODE BEGIN 2 */
	SPI_GPIO_Init();
	DMA_Init();
	uint8_t test_data[4] = {0xAA, 0xBB, 0xCC, 0xDD};
	DMA2_config_SPI1_TX((uint32_t)test_data, 4);

	ST7735_Init();              // 1. 초기화 (이전 단계에서 만든 함수)
	ST7735_FillScreen(0x0000);  // 2. 검정색으로 배경 채우기
	ST7735_WriteString(10, 50, "Hello World", Font_7x10, 0xFFFF, 0x0000);
	PWM_TIM5_CH1_Init(1000);
	PWM_TIM5_CH1_Setduty(80); //80% pwm duty
	PWM_TIM1_Base_Init(5000);
	PWM_TIM1_CH1_Init();
	PWM_TIM1_CH2_Init();
	PWM_TIM1_CH3_Init();
	Encoder_TIM4_Init();
	Usart3_TX_Init(115200);
	DMA_USART3_Init();
	TIM2_Init();
	Subsystem_initialize();
//	PWM_TIM1_CH1_Setduty(0.5);
//	PWM_TIM1_CH2_Setduty(0);
//	PWM_TIM1_CH3_Setduty(0);
	Can1_Init();
	Can1_Filter_Config();
	I2C1_DMA_Init();
	ADC_Init();
	Iq_ref = 1.0f;
	Wc = 1/Ts;
	Kpc = Ls*Wc;
	Kic = Rs*Wc;
//	PWM_TIM1_CH1_Setduty(0.5);
/* USER CODE END RTOS_EVENTS */
/* Start scheduler */

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of motorControl */
  motorControlHandle = osThreadNew(mControl, NULL, &motorControl_attributes);

  /* creation of SPI */
  SPIHandle = osThreadNew(SPI_T, NULL, &SPI_attributes);

  /* creation of CAN */
  CANHandle = osThreadNew(CAN_T, NULL, &CAN_attributes);

  /* creation of UART */
  UARTHandle = osThreadNew(UART_T, NULL, &UART_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = 0x00009000U;
  RCC_ClkInitStruct.APB2CLKDivider = 0x00008000U;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   static uint8_t MACAddr[6];

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
  heth.Init.TxDesc = DMATxDscrTab;
  heth.Init.RxDesc = DMARxDscrTab;
  heth.Init.RxBuffLen = 1524;

  /* USER CODE BEGIN MACADDRESS */

  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }

  memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
  TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
  TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
  TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief USB_OTG_FS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin|LD3_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
float ed = 0;
float eq = 0;
float ed_km1 = 0;
float eq_km1 = 0;
float Va = 0;
float Vb = 0;
float Vc = 0;
float Vd_pi = 0; float Vd_km1 = 0; float Vd = 0;
float Vq_pi = 0; float Vq_km1 = 0; float Vq = 0;

float flux = 0.0035;
float theta_rad_prev = 0;
float V_bus = 12.0f;
void get_motor_status(){
	theta_rad = Process_Encoder_Data();
	theta_degree = theta_rad * 180 / pi;
	angle_e = theta_rad * pole_pairs;
	angle_e = fmodf(angle_e, 2.0f * pi) - 2.17058086;
	speed_rad = (theta_rad - theta_rad_prev)/Tc;
	speed_rpm = speed_rad * 60 / (2*pi);
	theta_rad_prev = theta_rad;
}
void ADC_IRQHandler(void) {
    if (ADC1->SR & (1 << 2)) { // JEOC 비트 (Bit 2)가 1인지 확인
    	ADC1->SR = ~(1 << 2);
        // 변환된 전류 데이터 읽기
    	float V_pin_a = (float)(ADC1->JDR1) * (3.3f / 4095.0f);
    	float V_pin_b = (float)(ADC1->JDR2) * (3.3f / 4095.0f);
    	I_a = (V_pin_a - 1.65f) / (0.005f * 10.0f);
    	I_b = (V_pin_b - 1.65f) / (0.005f * 10.0f);

        I_c = -I_a - I_b;
        float I_alpha = I_a;
        float I_beta = (I_a + 2.0f * I_b) / sqrtf(3.0f);

        float cos_t = cosf(angle_e);
        float sin_t = sinf(angle_e);

         Id =  I_alpha * cos_t + I_beta * sin_t;
         Iq = -I_alpha * sin_t + I_beta * cos_t;

        //PI 전류제어
        ed = 0 - Id;
        eq = Iq_ref - Iq;

        Vd_pi = Vd_km1 + Kpc * (ed - ed_km1) + Kic*Tc*ed;
		Vq_pi = Vq_km1 + Kpc * (eq - eq_km1) + Kic*Tc*eq;

		ed_km1 = ed; Vd_km1 = Vd_pi;
        eq_km1 = eq; Vq_km1 = Vq_pi;

        Vd = Vd_pi - speed_rad * Ls * Iq;
        Vq = Vq_pi + speed_rad * Ls * Id + speed_rad * flux;
        //Vd = 0;
        //Vq = 5;

		float V_alpha = Vd * cos_t - Vq * sin_t;
		float V_beta  = Vd * sin_t + Vq * cos_t;

		Va = V_alpha;
		Vb = (-V_alpha + sqrtf(3.0f) * V_beta) / 2.0f;
		Vc = (-V_alpha - sqrtf(3.0f) * V_beta) / 2.0f;

		float duty_a = (Va / V_bus) + 0.5f;
		float duty_b = (Vb / V_bus) + 0.5f;
		float duty_c = (Vc / V_bus) + 0.5f;

		if (duty_a > 1.0f) duty_a = 1.0f; else if (duty_a < 0.0f) duty_a = 0.0f;
		if (duty_b > 1.0f) duty_b = 1.0f; else if (duty_b < 0.0f) duty_b = 0.0f;
		if (duty_c > 1.0f) duty_c = 1.0f; else if (duty_c < 0.0f) duty_c = 0.0f;

		PWM_TIM1_CH1_Setduty(duty_a);
		PWM_TIM1_CH2_Setduty(duty_b);
		PWM_TIM1_CH3_Setduty(duty_c);
//		PWM_TIM1_CH1_Setduty(0.3);
//		PWM_TIM1_CH2_Setduty(0.0);
//		PWM_TIM1_CH3_Setduty(0.0);
		gCount += Ts;
		time = gCount;

        GPIOG->ODR ^= (1 << 0); //확인용 토글

    }

    if (ADC2->SR & (1 << 2)) {
        ADC2->SR &= ~(1 << 2);
    }
}
void TIM2_IRQHandler(void) {
    if (TIM2->SR & (1<<0)) {
        TIM2->SR &= ~(1<<0);
//        rtU.theta = theta_rad;   // 위치 피드백 연결
//        rtU.speed_rad = speed_rad;    // 속도 피드백 연결
//        Subsystem_step();
//        motor_input((float)rtY.input);
//       	gCount += Ts;
//        time = gCount;
    }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	get_motor_status();
    osDelay(0.2);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_mControl */
/**
* @brief Function implementing the motorControl thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_mControl */
void mControl(void *argument)
{

  /* USER CODE BEGIN mControl */
  /* Infinite loop */
  for(;;)
  {

    osDelay(1);
  }
  /* USER CODE END mControl */
}

/* USER CODE BEGIN Header_SPI_T */
/**
* @brief Function implementing the SPI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SPI_T */
void SPI_T(void *argument)
{
  /* USER CODE BEGIN SPI_T */
  /* Infinite loop */
  for(;;)
  {
	  //
	  sprintf(buf, "RPM: %5d", (int)speed_rpm);
	  ST7735_WriteString(10, 50, buf, Font_7x10, 0xFFFF, 0x0000);
	  spi_count++;
    osDelay(50);
  }
  /* USER CODE END SPI_T */
}

/* USER CODE BEGIN Header_CAN_T */
/**
* @brief Function implementing the CAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CAN_T */
void CAN_T(void *argument)
{
  /* USER CODE BEGIN CAN_T */

  for(;;)
  {
	  mCount++;
	  desired_theta_deg = Can1_Receive_Handler(desired_theta_deg);
	  rtU.ref = desired_theta_deg * pi / 180.0f;
	  Can1_Send_MotorStatus(theta_degree, speed_rpm);
    osDelay(1);
  }
  /* USER CODE END CAN_T */
}

/* USER CODE BEGIN Header_UART_T */
/**
* @brief Function implementing the UART thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UART_T */
void UART_T(void *argument)
{
  /* USER CODE BEGIN UART_T */
  /* Infinite loop */
  for(;;)
  {
	  printf("%.2f, %.2f\n", time, speed_rad);
    osDelay(10);
  }
  /* USER CODE END UART_T */
}

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
