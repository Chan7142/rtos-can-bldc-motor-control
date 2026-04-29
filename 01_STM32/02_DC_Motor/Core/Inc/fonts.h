/* vim: set ai et ts=4 sw=4: */
#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>
#include "gpio.h"
#include "spi.h"


typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

void ST7735_Init(void);
void ST7735_HW_Reset(void);
void ST7735_FillScreen(uint16_t color);
void ST7735_SetAddressWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);


void ST7735_WriteCommand(uint8_t cmd);
void ST7735_WriteData(uint8_t data);


void A0_pin_set(void);
void A0_pin_reset(void);
void RESET_pin_set(void);
void RESET_pin_reset(void);
void ST7735_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7735_DrawChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
#endif /* __FONTS_H__ */
