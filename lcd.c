#include "lcd.h"
#include <16F877A.h>

void lcd_send_nibble(uint8_t nibble) {
    output_bit(LCD_DATA4, bit_test(nibble, 0));
    output_bit(LCD_DATA5, bit_test(nibble, 1));
    output_bit(LCD_DATA6, bit_test(nibble, 2));
    output_bit(LCD_DATA7, bit_test(nibble, 3));
    output_high(LCD_ENABLE_PIN);
    delay_us(2);
    output_low(LCD_ENABLE_PIN);
}

void lcd_send_byte(uint8_t address, uint8_t n) {
    output_low(LCD_RS_PIN);
    delay_us(60);
    if (address)
        output_high(LCD_RS_PIN);
    else
        output_low(LCD_RS_PIN);
    delay_us(60);
    output_low(LCD_ENABLE_PIN);
    lcd_send_nibble(n >> 4);
    lcd_send_nibble(n & 0x0F);
}

void lcd_init() {
    output_low(LCD_RS_PIN);
    output_low(LCD_RW_PIN);
    output_low(LCD_ENABLE_PIN);
    delay_ms(15);
    for (int i = 0; i < 3; i++) {
        lcd_send_nibble(0x03);
        delay_ms(5);
    }
    lcd_send_nibble(0x02);
    lcd_send_byte(0, 0x28);
    lcd_send_byte(0, 0x0C);
    lcd_send_byte(0, 0x06);
    lcd_send_byte(0, 0x01);
    delay_ms(5);
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t address;
    if (y != 1)
        address = 0x40;
    else
        address = 0;
    address += x - 1;
    lcd_send_byte(0, 0x80 | address);
}

void lcd_putc(char c) {
    switch (c) {
        case '\f':
            lcd_send_byte(0, 1);
            delay_ms(2);
            break;
        case '\n':
            lcd_gotoxy(1, 2);
            break;
        case '\b':
            lcd_send_byte(0, 0x10);
            break;
        default:
            lcd_send_byte(1, c);
            break;
    }
}

void lcd_puts(const char* s) {
    while (*s) {
        lcd_putc(*s++);
    }
}

void lcd_clear() {
    lcd_send_byte(0, 1);
    delay_ms(2);
}

