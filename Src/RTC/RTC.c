#include "RTC_Interface.h"
#include "i2c.h"

#define DS3231_ADDRESS 0xD0
uint8_t get_time[7];

float TEMP;
char buffer[15];




TIME RTC_Time;

TIME* RTC_Init (void)
{
//		Set_Time(00, 50, 16, 5, 9, 3, 22);      //sec,min,hour,dow,dom,month,year
			Get_Time();                              //Getting instance of now timing , we will implement it to STM_RTC
//		DGUS_Hours=Convert_Decimal_To_Hexadecimal(20);//time.hour;
//		DGUS_Minutes=Convert_Decimal_To_Hexadecimal(30);//time.minutes;
//		DGUS_Seconds=Convert_Decimal_To_Hexadecimal(00);//time.seconds;
//		DGUS_Years=Convert_Decimal_To_Hexadecimal(time.year);
//		DGUS_Months=Convert_Decimal_To_Hexadecimal(time.month);
//		DGUS_Days=Convert_Decimal_To_Hexadecimal(time.dayofmonth);
	
	return &RTC_Time;
}
	
// Convert normal decimal numbers to binary coded decimal
uint8_t decToBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
int bcdToDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}


// function to set time

void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

void Get_Time (void)
{
	
	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000); 
	
	RTC_Time.seconds = bcdToDec(get_time[0]);
	RTC_Time.seconds=Convert_Decimal_To_Hexadecimal(RTC_Time.seconds);
	RTC_Time.minutes = bcdToDec(get_time[1]);
	RTC_Time.minutes=Convert_Decimal_To_Hexadecimal(RTC_Time.minutes);
	RTC_Time.hour = bcdToDec(get_time[2]);
	RTC_Time.hour=Convert_Decimal_To_Hexadecimal(RTC_Time.hour);
	RTC_Time.dayofweek = bcdToDec(get_time[3]);
	RTC_Time.dayofweek=Convert_Decimal_To_Hexadecimal(RTC_Time.dayofweek);
	RTC_Time.dayofmonth = bcdToDec(get_time[4]);
	RTC_Time.dayofmonth=Convert_Decimal_To_Hexadecimal(RTC_Time.dayofmonth);
	RTC_Time.month = bcdToDec(get_time[5]);
	RTC_Time.month=Convert_Decimal_To_Hexadecimal(RTC_Time.month);
	RTC_Time.year = bcdToDec(get_time[6]);
	RTC_Time.year=Convert_Decimal_To_Hexadecimal(RTC_Time.year);	
}

float Get_Temp (void)
{
	uint8_t temp[2];

	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x11, 1, temp, 2, 1000);
	return ((temp[0])+(temp[1]>>6)/4.0);
}

void force_temp_conv (void)
{
	uint8_t status=0;
	uint8_t control=0;
	HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x0F, 1, &status, 1, 100);  // read status register
	if (!(status&0x04))
	{
		HAL_I2C_Mem_Read(&hi2c2, DS3231_ADDRESS, 0x0E, 1, &control, 1, 100);  // read control register
		HAL_I2C_Mem_Write(&hi2c2, DS3231_ADDRESS, 0x0E, 1, (uint8_t *)(control|(0x20)), 1, 100);
	}
}


uint16_t Convert_Decimal_To_Hexadecimal (uint16_t Decimal)
{
	
	uint8_t Hexadecimal=0;
	if ((Decimal<=9)&&(Decimal>0))
	{
		Hexadecimal=Decimal;
	}
	else if (((Decimal<=19)&&(Decimal>=10)))
	{
		Hexadecimal=Decimal+6;
	}
	else if (((Decimal<=29)&&(Decimal>=20)))
	{
		Hexadecimal=Decimal+12;
	}
	else if (((Decimal<=39)&&(Decimal>=30)))
	{
		Hexadecimal=Decimal+18;
	}
	else if (((Decimal<=49)&&(Decimal>=40)))
	{
		Hexadecimal=Decimal+24;
	}
	else if (((Decimal<=59)&&(Decimal>=50)))
	{
		Hexadecimal=Decimal+30;
	}
return Hexadecimal;
}
