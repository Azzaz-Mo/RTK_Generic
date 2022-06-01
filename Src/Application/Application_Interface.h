#ifndef APPLICATION_INTERFACE_H_
#define APPLICATION_INTERFACE_H_

#include "main.h"

void Activate(uint8_t Tag_Number);
void Application_Init (void);
uint8_t Application (void);
void Acknowledge (void);
void Mute (void);
void Reset (void);
void Test(void);
void Password_Verification(void);
void Alarm_Trip_Config(uint16_t Tag_Value);
void RTC_Handler (void);
void RTC_Loop (void);
void Event_Handler (uint8_t Tag_Log,uint8_t Status);
void Debug_M (void);


#endif