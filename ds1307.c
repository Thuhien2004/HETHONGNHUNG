#include <16F877A.h>
#include <i2c.h>
#include "ds1307.h"

#define DS1307_I2C_ADDRESS 0xD0

void RTC_Init() {
    i2c_init();
}

void RTC_Set(RTC_Time* time) {
    i2c_start();
    i2c_write(DS1307_I2C_ADDRESS);
    i2c_write(0x00);
    i2c_write(((time->seconds / 10) << 4) + (time->seconds % 10));
    i2c_write(((time->minutes / 10) << 4) + (time->minutes % 10));
    i2c_write(((time->hours / 10) << 4) + (time->hours % 10));
    i2c_write(0x00); // Day of week, not used here
    i2c_write(((time->day / 10) << 4) + (time->day % 10));
    i2c_write(((time->month / 10) << 4) + (time->month % 10));
    i2c_write(((time->year / 10) << 4) + (time->year % 10));
    i2c_stop();
}

RTC_Time RTC_Get() {
    RTC_Time time;
    i2c_start();
    i2c_write(DS1307_I2C_ADDRESS);
    i2c_write(0x00);
    i2c_start();
    i2c_write(DS1307_I2C_ADDRESS | 0x01);
    time.seconds = i2c_read() & 0x7F;
    time.minutes = i2c_read() & 0x7F;
    time.hours = i2c_read() & 0x3F;
    i2c_read(); // Day of week, not used here
    time.day = i2c_read() & 0x3F;
    time.month = i2c_read() & 0x1F;
    time.year = i2c_read();
    i2c_stop();
    return time;
}

