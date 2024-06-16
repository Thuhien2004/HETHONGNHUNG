#include "lcd_i2c.h"
#include <16F877A.h>
#include <i2c.c>

// Global variable
uint8_t lcd_backlight = LCD_BACKLIGHT;

// Private function prototypes
void lcd_i2c_send(uint8_t value);
void lcd_i2c_pulse_enable(uint8_t value);
void lcd_i2c_send_byte(uint8_t value, uint8_t mode);
void lcd_i2c_command(uint8_t value);
void lcd_i2c_write_char(uint8_t value);

void lcd_i2c_send(uint8_t value) {
    i2c_start();
    i2c_write(LCD_I2C_ADDR << 1);
    i2c_write(value | lcd_backlight);
    i2c_stop();
}

void lcd_i2c_pulse_enable(uint8_t value) {
    lcd_i2c_send(value | En);
    delay_us(1);
    lcd_i2c_send(value & ~En);
    delay_us(50);
}

void lcd_i2c_send_byte(uint8_t value, uint8_t mode) {
    uint8_t high_nibble = value & 0xF0;
    uint8_t low_nibble = (value << 4) & 0xF0;
    lcd_i2c_send(high_nibble | mode);
    lcd_i2c_pulse_enable(high_nibble | mode);
    lcd_i2c_send(low_nibble | mode);
    lcd_i2c_pulse_enable(low_nibble | mode);
}

void lcd_i2c_command(uint8_t value) {
    lcd_i2c_send_byte(value, 0);
}

void lcd_i2c_write_char(uint8_t value) {
    lcd_i2c_send_byte(value, Rs);
}

void lcd_i2c_init() {
    delay_ms(50);
    lcd_i2c_send(lcd_backlight);
    delay_ms(1000);

    lcd_i2c_command(0x03);
    delay_ms(5);
    lcd_i2c_command(0x03);
    delay_us(150);
    lcd_i2c_command(0x03);
    lcd_i2c_command(0x02);

    lcd_i2c_command(LCD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINE | LCD_5x8DOTS);
    lcd_i2c_command(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF);
    lcd_i2c_command(LCD_CLEAR_DISPLAY);
    delay_ms(2);
    lcd_i2c_command(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT | LCD_ENTRY_SHIFT_DECREMENT);
}

void lcd_i2c_clear() {
    lcd_i2c_command(LCD_CLEAR_DISPLAY);
    delay_ms(2);
}

void lcd_i2c_gotoxy(uint8_t x, uint8_t y) {
    uint8_t address;
    switch(y) {
        case 0: address = 0x80; break;
        case 1: address = 0xC0; break;
        case 2: address = 0x94; break;
        case 3: address = 0xD4; break;
    }
    address += x;
    lcd_i2c_command(address);
}

void lcd_i2c_putc(char c) {
    lcd_i2c_write_char(c);
}

void lcd_i2c_puts(const char* s) {
    while (*s) {
        lcd_i2c_putc(*s++);
    }
}

