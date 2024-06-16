#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} RTC_Time;

void RTC_Init();
void RTC_Set(RTC_Time* time);
RTC_Time RTC_Get();

#endif // DS1307_H

