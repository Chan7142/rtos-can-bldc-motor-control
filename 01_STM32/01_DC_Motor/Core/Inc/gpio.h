#ifndef GPIO_H__
#define GPIO_H__
#include "rcc.h"
#include <stdint.h>

#define GPIOA_BASE		0x40020000
#define GPIOB_BASE		0x40020400
#define GPIOC_BASE		0x40020800
#define GPIOD_BASE		0x40020C00
#define GPIOE_BASE		0x40021000
#define GPIOF_BASE		0x40021400
#define GPIOG_BASE		0x40021800
#define GPIOH_BASE		0x40021C00
#define GPIOI_BASE		0x40022000
#define GPIOJ_BASE		0x40022400
#define GPIOK_BASE		0x40022800

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}Gpio_Struct;

#define GPIOA ((Gpio_Struct*)GPIOA_BASE)
#define GPIOB ((Gpio_Struct*)GPIOB_BASE)
#define GPIOC ((Gpio_Struct*)GPIOC_BASE)
#define GPIOD ((Gpio_Struct*)GPIOD_BASE)
#define GPIOE ((Gpio_Struct*)GPIOE_BASE)
#define GPIOF ((Gpio_Struct*)GPIOF_BASE)
#define GPIOG ((Gpio_Struct*)GPIOG_BASE)
#define GPIOH ((Gpio_Struct*)GPIOH_BASE)
#define GPIOI ((Gpio_Struct*)GPIOI_BASE)
#define GPIOJ ((Gpio_Struct*)GPIOJ_BASE)
#define GPIOK ((Gpio_Struct*)GPIOK_BASE)

void GPIO_pin_Mode(Gpio_Struct* GPIOx, uint8_t pin, uint8_t mode);
void GPIO_Write_Pin(Gpio_Struct* GPIOx, uint8_t pin, uint8_t logic);
uint8_t GPIO_Read_Pin(Gpio_Struct* GPIOx, uint8_t pin);
void GPIO_Clock_Enable(Gpio_Struct* GPIOx);
void GPIO_Speed_Set(Gpio_Struct* GPIOx, uint8_t pin, uint8_t speed);

#endif /* __GPIO_H__ */
