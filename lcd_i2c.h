#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdint.h>

// Define the I2C address for the LCD
#define LCD_I2C_ADDR 0x27

// Function declarations
void lcd_i2c_init(void);
void lcd_i2c_gotoxy(uint8_t x, uint8_t y);
void lcd_i2c_putc(char c);
void lcd_i2c_puts(char* s);  // S?a khai báo hàm này
void lcd_i2c_clear(void);
void lcd_i2c_send_byte(uint8_t value, uint8_t mode);

#endif // LCD_I2C_H

