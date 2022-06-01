#ifndef DGUS_INTERFACE_H_
#define DGUS_INTERFACE_H_

#include "main.h"




void DGUS_Initialization(void);
uint16_t   DGUS_Check_Msg(void);
void HMI_Status (uint8_t Tag_Number,uint8_t Tag_Status);
extern uint8_t A_T_Arr[25];
uint16_t * Get_Variable (void);
uint16_t * Get_Text (void);
void Alarm_On (uint8_t Time);
void Test_Tags_DGUS (uint8_t * Test_Ptr);
void Edit_Mode_Page_Switch (void);
void Flash_Load_Data(void);
void DGUS_RTC (RTC_TimeTypeDef* DGUS_RTC_Ptr);









#endif