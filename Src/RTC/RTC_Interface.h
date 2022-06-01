#ifndef __RTC_INTERFACE_H
#define __RTC_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} TIME;

TIME* RTC_Init (void);
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
float Get_Temp (void);
void Get_Time (void);
void force_temp_conv (void);
uint16_t Convert_Decimal_To_Hexadecimal (uint16_t Decimal);





#ifdef __cplusplus
}
#endif

#endif  
