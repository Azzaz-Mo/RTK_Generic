#include "DGUS_Interface.h"
#include "HMI_Interface.h"
#include "HMI_Cfg.h"
#include "DGUS_Cfg.h"
#include "Configurations.h"

uint8 Save_Flag=0;
uint8 Send_Normal_Flag=0;
uint8 Serial_Event_Flag=0;
uint8 A_T_Arr[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

uint8_t DGUS_Hours,DGUS_Minutes,DGUS_Seconds;

/*this is the looping function for triggering HMI module */
uint16_t* Msg_DGUS_Ptr=0;
uint16_t  Msg_DGUS=0;
uint16 Msg_DGUS_Variable[MSG_INDEX]={0};
uint8  Msg_DGUS_Variable_Status=NOT_OK;
uint16 Msg_DGUS_Text[MAX_SIZE]={0};
uint8  Msg_DGUS_Text_Status=NOT_OK;
uint8_t Msg_Length_DGUS=0;
uint8_t Increment_DGUS=0;

uint16_t  DGUS_Check_Msg(void)
{
		Msg_DGUS_Ptr[TYPE_INDEX]=NOT_OK;
		Msg_DGUS_Ptr=HMI_Check_Msg();
		if (*Msg_DGUS_Ptr==VARIABLE)
		{
				Msg_DGUS_Variable[TYPE_INDEX]=Msg_DGUS_Ptr[TYPE_INDEX];
				Msg_DGUS_Variable[ADDRESS_INDEX]=Msg_DGUS_Ptr[ADDRESS_INDEX];
				Msg_DGUS_Variable[VALUE_INDEX]=Msg_DGUS_Ptr[VALUE_INDEX];
				Msg_DGUS_Variable_Status=OK;
		}
		else
		{
				Msg_DGUS_Text_Status=OK;
				Msg_DGUS_Text[TYPE_INDEX]=Msg_DGUS_Ptr[TYPE_INDEX];
				Msg_Length_DGUS=Msg_DGUS_Ptr[TYPE_INDEX];
				Msg_DGUS_Text[ADDRESS_INDEX]=Msg_DGUS_Ptr[ADDRESS_INDEX];
				for(Increment_DGUS=1;Increment_DGUS<=Msg_Length_DGUS;Increment_DGUS++)
				{
					Msg_DGUS_Text[Increment_DGUS+1]=Msg_DGUS_Ptr[Increment_DGUS+1];
				}
		}
		return Msg_DGUS_Ptr[TYPE_INDEX];
}

uint16_t* Get_Variable (void)
{
	return Msg_DGUS_Variable;
}

uint16_t* Get_Text (void)
{
	return Msg_DGUS_Text;
}

void Test_Tags_DGUS (uint8_t * Test_Ptr)
{
	uint8_t i=0;
	
	for (i=1;i<=ANN_TAG_NUMBER;i++)
	{
		DGUS_SendVal(i,Test_Ptr[i]);
		DGUS_Beep(100);
	}
	HAL_Delay(800);
	
	
}
void DGUS_Initialization(void)
{
	HMI_Init(); 
	DGUS_Beep(100);
}

void Alarm_On (uint8_t Time)
{
	DGUS_Beep(Time);
}
/* this function is responsible for direct flashing */
void HMI_Status (uint8_t Tag_Number,uint8_t Tag_Status)
{
	DGUS_SendVal(Tag_Number,Tag_Status);
	
}

void Edit_Mode_Page_Switch (void)
{
	DGUS_Page_Switch();
}
/* This function has POD , since the load of data must be in Flash module and displaying here , not together */
void Flash_Load_Data(void)
{
	uint16_t* Read_Ptr=(uint16_t*)START_SAVE_ADDRESS;
	uint8_t Increment_DGUS_2=0;
	uint8_t Text[32]={0};
	uint8_t Counter=0;
	uint16_t Addressses[ANN_TAG_NUMBER]={0};
	for(Increment_DGUS=0;Increment_DGUS<ANN_TAG_NUMBER;Increment_DGUS++)
	{
		Addressses[Increment_DGUS]=0x100+(0x10*Increment_DGUS);
	}
	for(Increment_DGUS=1;Increment_DGUS<=ANN_TAG_NUMBER;Increment_DGUS++)
	{
		Text[1]=Addressses[Increment_DGUS-1]>>8;                           //Address
		Text[2]=Addressses[Increment_DGUS-1];
		for(Increment_DGUS_2=1;Increment_DGUS_2<=16;Increment_DGUS_2++)
		{
			if(Read_Ptr[Increment_DGUS_2]<0xFF)
			{
				Text[Increment_DGUS_2+2]=Read_Ptr[((Increment_DGUS_2-1)+(Increment_DGUS-1)*INCREMENT_VALUE)];
				Counter++;
			}
		}
		Text[0]=Counter;
			DGUS_SendText(Text);
			Counter=0;
	}
}

void DGUS_RTC (RTC_TimeTypeDef* DGUS_RTC_Ptr)
{
	DGUS_Seconds=DGUS_RTC_Ptr->Seconds;
	DGUS_Minutes=DGUS_RTC_Ptr->Minutes;
	DGUS_Hours=DGUS_RTC_Ptr->Hours;
	
	DGUS_SendVal(RTC_HOURS_ADD,DGUS_Hours);
	DGUS_SendVal(RTC_MINUTES_ADD,DGUS_Minutes);
	DGUS_SendVal(RTC_SECONDS_ADD,DGUS_Seconds);
}
