#include "gpio.h"

void GPIO_pin_Mode(Gpio_Struct* GPIOx, uint8_t pin, uint8_t mode){
	GPIOx->MODER &= ~(3UL << (pin * 2)); // 초기화
	GPIOx->MODER |= (mode<<(pin*2));
}

void GPIO_Write_Pin(Gpio_Struct* GPIOx, uint8_t pin, uint8_t logic){
	if(logic) GPIOx->BSRR = (1 << pin);
	else GPIOx->BSRR = (1 << (pin+16));
}

uint8_t GPIO_Read_Pin(Gpio_Struct* GPIOx, uint8_t pin){
	return ((GPIOx->IDR & (1 << pin)) ? 1 : 0);
}
void GPIO_Clock_Enable(Gpio_Struct* GPIOx) {
    if      (GPIOx == GPIOA) RCC->AHB1ENR |= (1 << 0);
    else if (GPIOx == GPIOB) RCC->AHB1ENR |= (1 << 1);
    else if (GPIOx == GPIOC) RCC->AHB1ENR |= (1 << 2);
    else if (GPIOx == GPIOD) RCC->AHB1ENR |= (1 << 3);
    else if (GPIOx == GPIOE) RCC->AHB1ENR |= (1 << 4);
    else if (GPIOx == GPIOF) RCC->AHB1ENR |= (1 << 5);
    else if (GPIOx == GPIOG) RCC->AHB1ENR |= (1 << 6);
    else if (GPIOx == GPIOH) RCC->AHB1ENR |= (1 << 7);
    else if (GPIOx == GPIOI) RCC->AHB1ENR |= (1 << 8);
    else if (GPIOx == GPIOJ) RCC->AHB1ENR |= (1 << 9);
    else if (GPIOx == GPIOK) RCC->AHB1ENR |= (1 << 10);

    volatile uint32_t dummy = RCC->AHB1ENR;
    (void)dummy;
}

void GPIO_Speed_Set(Gpio_Struct* GPIOx, uint8_t pin, uint8_t speed){
	GPIOx->OSPEEDR &= ~(3UL << (pin * 2));
	GPIOx->OSPEEDR |= (speed<<(pin*2));
}
