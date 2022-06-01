#ifndef HMI_INTERFACE_H_
#define HMI_INTERFACE_H_
#include "main.h"
#include "usart.h"
#include "Platform_Types.h"



void serial1Event();
void DGUS_Beep(uint16_t bTime);
void DGUS_SendVal(int iAdr, int iVal);
void ALL_ON (void);
void ALL_OFF (void);
void Send_Normal (void);
void DGUS_Page_Switch (void);
void HMI_Init(void);
void Delay_Send(void);

extern uint8_t Save_Flag;
extern uint8_t Send_Normal_Flag;
extern uint8_t Serial_Event_Flag;


extern	uint8_t	 tx_buff;
extern int  Address;
extern int  Value;

uint16_t*	HMI_Check_Msg(void);
void Safety_Condition (void);
void RESET_Buff(void);
void DGUS_SendText (uint8_t* Ptr);










#endif