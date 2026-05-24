#ifndef DWT_H
#define DWT_H
#include <stdint.h>
#define DWT_LAR      (*(volatile uint32_t *)0xE0001FB0) // Lock Access Register
#define DWT_CYCCNT   (*(volatile uint32_t *)0xE0001004) // Cycle Count Register
#define DWT_CONTROL  (*(volatile uint32_t *)0xE0001000) // Control Register
#define SCB_DEMCR    (*(volatile uint32_t *)0xE000EDFC) // Debug Exception and Monitor Control
//#define DEMCR           (*(volatile uint32_t *)0xE000EDFC)
#define TRCENA_BIT      (1 << 24)
void DWT_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);


#endif
