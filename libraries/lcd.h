#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"



void i2c_write_byte(uint8_t val);
static void inline lcd_char(char val);
void lcd_toggle_enable(uint8_t val);
void lcd_send_byte(uint8_t val, int mode);
void lcd_clear(void);
void lcd_set_cursor(int line, int position);
void lcd_string(const char *s);
void lcd_init();

#endif // LCD_H
