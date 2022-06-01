#include "Configurations.h"

#include "Application_Cfg.h"
#include "DGUS_Interface.h"
#include "Application_Interface.h"
#include "Input_Scan_Interface.h"
#include "tim.h"
#include "usart.h"
#include "RTC_Interface.h"
#include "Flash_Interface.h"
#include "rtc.h"

uint8_t   State=0;    


uint8_t*  Dispatch_Ptr=0;
uint8_t   Increment_App=0;
uint8_t   Target_Tag[ANN_TAG_NUMBER]={0};
uint8_t   System_Trigger=0;
uint8_t   Flash_Status=0;
uint8_t   Beep=NOT_OK;
uint16_t  Msg_Application=0;
uint16_t* Msg_Variable_Ptr=0;
uint16_t  Msg_Variable[MSG_INDEX]={0};
uint16_t* Msg_Text_Ptr=0;
uint16_t  Msg_Text[TEXT+1]={0};
uint8_t   Msg_Text_Length=0;

uint32_t Counter_ms=0;
uint64_t Counter_Ms=0;
uint32_t Start_Operation_Time=0;
uint32_t End_Operation_Time=0;
uint32_t Task_Duration=0;
uint8_t Tag_Status_Array[ANN_TAG_NUMBER]={0};

uint16_t Debug_Array[10]={0x8,0x100,0x68,0x61,0x7A,0x65,0x65,0x65,0x65,0x6D};
/********************************* RTC **************************************************/
TIME APP_Time;
TIME* RTC_Ptr=0;
RTC_TimeTypeDef gTime={0};
RTC_DateTypeDef gDate={0};

struct {
	uint8_t Years;
	uint8_t Months;
	uint8_t Days;
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
}APP_RTC;
/****************************************************************************************/
/********************************* LOG **************************************************/
uint8_t Log[ANN_TAG_NUMBER+1][8+1]={0};
uint8_t Counter_Log=0;
/****************************************************************************************/
/********************************* (Scheduler) TIM2 Triggered every half second *******************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
			Counter_Log++;
			
			if(htim->Instance==TIM2)
			{
							State=FLASH_STATE;
							if  (Flash_Status==OK)  //can be replaced by Flash_Status^=Flash_Status;
							{
								Flash_Status=NOT_OK;
							}
							else
							{
								Flash_Status=OK;
							}
			}
			if (Counter_Log==2)
			{
				                               //POD
			}
			if(htim->Instance==TIM1)      //ms
			{
							Counter_ms++;
			}
			if(htim->Instance==TIM3)      //Ms
			{
							Counter_Ms++;
			}
}
/******************************************************************************************************************/
uint8_t Recieve_Esp[2]={0};
uint8_t Transmit_A5[]={0xA5,3,1,1,1,22,3,8,13,45,0,2,1,2,22,3,8,14,30,0,3,1,2,22,3,8,15,45,0,0x5A};
uint8_t Transmit_5A=0x5A;

uint16_t Msg_Flash[10]={8,1,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8};
uint16_t Msg_Flash2[10]={8,1,0x9,0x10,0x11,0x12,0x13,0x14,0x15,0x16};
uint16_t Msg_Flash3[10]={8,3,0x17,0x18,0x19,0x20,0x21,0x22,0x23,0x24};

/******************************************************************************************************************/
/********************************************* APPLICATION INITIALIZATION ******************************************************/
void Application_Init (void)
{
	DGUS_Initialization();
	HAL_TIM_Base_Start_IT(&htim1);                                        //POD need to add HAL module 
	HAL_TIM_Base_Start_IT(&htim2);                                        //POD
	HAL_UART_Receive_DMA(&huart2,Recieve_Esp,2);                          //POD 
	HAL_UART_Transmit_IT(&huart2,Transmit_A5,30);                         //POD
	HAL_UART_Transmit(&huart1,&Transmit_5A,2,10);
	//Debug_M();	
	//Flash_Load_Data_2(0x100);
	//Flash_Load_Data();																												
																																				//	Flash_Load_Data();
																																				//	Save_Tag_To_Flash(Msg_Flash);
																																				//	Save_Tag_To_Flash(Msg_Flash2);
																																				//	Save_Tag_To_Flash(Msg_Flash3);
	//RTC_Handler();																										  //  Get data from External RTC and fetch it into the Internal

	for (Increment_App=1;Increment_App<=ANN_TAG_NUMBER;Increment_App++)
		{
				//Tag[Increment_App].Status=OK;
				Tag[Increment_App].Type=ALARM;                                  //POD
		}
}
/*****************************************************************************************************************/				
/***************************************** APPLICATION PROGRAM ***************************************************/
/* this is the main application function for the annunciator */

uint8_t Application (void)
{
	

	uint8_t Error_Status=NOT_OK;
	switch(State)
	{
/*************************************		INITIAL_STATE   ********************************************************/
		case INITIAL_STATE:
		{	
			/* this block is responsible for scanning the activated pins for tag activation. */
			Dispatch_Ptr=Input_Scan();
			//Increment_App=*Dispatch_Ptr;          //POD
			for (Increment_App=1;Increment_App<=TOTAL_INPUTS;Increment_App++)
				{
					if(Increment_App<=ANN_TAG_NUMBER)    //search for Input Tags
					{
											Target_Tag[Increment_App]=Dispatch_Ptr[Increment_App];
											if(Target_Tag[Increment_App]==OK)
												{
													Tag[Increment_App].Status=OK;
													State=FLASH_STATE;
													if(Tag[Increment_App].Last_Status==NOT_OK)
													{
														Event_Handler(Increment_App,OK);					//handler is responsible for the first change only for event log.
													}
													Tag[Increment_App].Last_Status=OK;
													
												}
												else
												{
													if(Tag[Increment_App].Last_Status==OK)
													{
														Event_Handler(Increment_App,NOT_OK);			//call handler
													}
													Tag[Increment_App].Last_Status=NOT_OK;
												}
					}
					else                               								  //search for non Input Tags (Mute,Ack...etc).
					{
												if((Increment_App==ACK)&&(Dispatch_Ptr[Increment_App]==OK))
												{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
													Acknowledge();
												}
												else if((Increment_App==RESET)&&(Dispatch_Ptr[Increment_App]==OK))
												{
													Reset();
												}
												else if((Increment_App==MUTE)&&(Dispatch_Ptr[Increment_App]==OK))
												{
													Mute();
												}
												else if((Increment_App==AC)&&(Dispatch_Ptr[Increment_App]==OK))
												{
													//here we call a function in DGUS to send cmd to HMI to handler f
												}
												else if((Increment_App==DC)&&(Dispatch_Ptr[Increment_App]==OK))
												{
													
												}
					}
				}
				
			/***********************************/
			/* this block is for recieving msgs */
				Msg_Application=DGUS_Check_Msg();
				if(Msg_Application>NOT_OK) 														//means there're variable or text
				{
							State=RECIEVE_STATE;
							
				}
  		/***********************************/
			}
			break;
/*****************************************************************************************************************/	
/*************************************		RECIEVE_STATE   ********************************************************/				
		case RECIEVE_STATE:
		{
				Msg_Variable_Ptr=Get_Variable(); 
		
			if (Msg_Variable_Ptr[TYPE_INDEX]==VARIABLE)
			{	
									Msg_Variable[ADDRESS_INDEX]=Msg_Variable_Ptr[ADDRESS_INDEX];
									Msg_Variable[VALUE_INDEX]=Msg_Variable_Ptr[VALUE_INDEX];
								
											switch (Msg_Variable[ADDRESS_INDEX])
											{
												case ACK :
													Acknowledge();
													break;
												case MUTE :
													Mute();
													break;
												case RESET :
													Reset();
													break;
												case TEST :
													Test();
													break;
												case PASSWORD_ADD:
													Password_Verification();
													break;
												case ALARM_TRIP_ADD:
													Alarm_Trip_Config(Msg_Variable[VALUE_INDEX]);
													break;
											}
												
			}
			else
			{
									Msg_Text_Ptr=Get_Text();
									Flash_Save_Data(Msg_Text_Ptr);
			}
							Msg_Variable[ADDRESS_INDEX]=0;
							Msg_Variable[VALUE_INDEX]=0;
							State=INITIAL_STATE;
		}
			break;
/*****************************************************************************************************************/	
/*************************************		ACTION_STATE   ********************************************************/				
		case ACTION_STATE:
		{
			//do something
			State=INITIAL_STATE;
		}
			break;
/*****************************************************************************************************************/	
/*************************************		FLASH_STATE   ********************************************************/						
		/* this stage you will go hard coded for further development ideas. */
		case FLASH_STATE:
		{
																									Start_Operation_Time=Counter_ms;
		RTC_Loop();               							  //call RTC for updating values
			
		
																									End_Operation_Time=Counter_ms;
																									Task_Duration=End_Operation_Time-Start_Operation_Time;
		for(Increment_App=1;Increment_App<=ANN_TAG_NUMBER;Increment_App++)
		{
			if(Tag[Increment_App].Status==OK)
			{

							if ((Tag[Increment_App].Ack==OK)||(Tag[Increment_App].Mute==OK))
							{
											Beep=NOT_OK;
											if(Tag[Increment_App].Ack==OK)
											{
																		HMI_Status(Increment_App,Tag[Increment_App].Type);
											}
											else //then the Mute is pressed
											{
																	if(Flash_Status==NOT_OK)
																	{
																		HMI_Status(Increment_App,NOT_OK);
																	}
																	else
																	{
																		HMI_Status(Increment_App,Tag[Increment_App].Type);
																	}
											}
							}
							else
							{
											Alarm_On(80);                  //design wise , must the function doesn't recieve parameters , since the application can not know the info of operating beep time
											if(Flash_Status==NOT_OK)
											{
															HMI_Status(Increment_App,NOT_OK);
											}
											else
											{
															HMI_Status(Increment_App,Tag[Increment_App].Type);
											}
				}
			}
			else
			{
				HMI_Status(Increment_App,NOT_OK);
			}
		}
	
		State=INITIAL_STATE;
	}
			break;
	}
	
}

/*****************************************************************************************************************/



void Alarm_Trip_Config(uint16_t Tag_Value)
{
	uint8_t Status=0;
	uint8_t Tag_Number=0;
	
	Status=Tag_Value%2;
	if(Status==1)
	{
		Tag_Number=(Tag_Value+1)/2;
	}
	else
	{ //ALARM EVEN
		Tag_Number=Tag_Value/2;
	}
	Tag[Tag_Number].Type=Status+1;
	
}
/***************************************************************************************************************/	
/*************************************		RTC    ********************************************************/	
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef DateToUpdate = {0};
	
void RTC_Handler (void)
{
	RTC_Ptr=RTC_Init();
	APP_Time.seconds=RTC_Ptr->seconds;
	APP_Time.minutes=RTC_Ptr->minutes;
	APP_Time.hour=RTC_Ptr->hour;
	APP_Time.dayofmonth=RTC_Ptr->dayofmonth;
	APP_Time.month=RTC_Ptr->month;
	APP_Time.year=RTC_Ptr->year;

	sTime.Hours = APP_Time.hour;
  sTime.Minutes = APP_Time.minutes;
  sTime.Seconds = APP_Time.seconds;

 HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
 
	DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = APP_Time.month;
  DateToUpdate.Date = APP_Time.dayofmonth;
  DateToUpdate.Year = APP_Time.year;

 HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);
}

void RTC_Loop (void)
{
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&gDate,RTC_FORMAT_BIN);
	APP_RTC.Years=gDate.Year;
	APP_RTC.Months=gDate.Month;
	APP_RTC.Days=gDate.Date;
	APP_RTC.Hours=gTime.Hours;
	APP_Time.minutes=gTime.Minutes;
	APP_Time.seconds=gTime.Seconds;
	DGUS_RTC(&gTime);
}
/*****************************************************************************************************************/	
/*************************************		BASIC OPERATIONAL FUNCTIONS   ********************************************************/				
void Acknowledge (void)
{
	uint8_t i=0;
	for(i=0;i<=ANN_TAG_NUMBER;i++)
	{
		if(Tag[i].Status==OK)
		{
			Tag[i].Ack=OK;
		}
	}
}
void Mute (void)
{
	uint8_t i=0;
	for(i=0;i<=ANN_TAG_NUMBER;i++)
	{
		if(Tag[i].Status==OK)
		{
			Tag[i].Mute=OK;
		}
	}
}
void Reset (void)
{
	uint8_t i=0;
	for(i=0;i<=ANN_TAG_NUMBER;i++)
	{
		Tag[i].Status=NOT_OK;
		Tag[i].Ack=NOT_OK;
		Tag[i].Mute=NOT_OK;
		//Tag[i].Last_Status=NOT_OK;     //To be Discussed with Dr.Ibrahim since if we reset the tags and it's hardware still on , so it will comes as new event to be recorded.
	}
}
void Test(void)
{
	for(Increment_App=1;Increment_App<=ANN_TAG_NUMBER;Increment_App++)
	{
		Tag_Status_Array[Increment_App]=Tag[Increment_App].Type;
	}
	Test_Tags_DGUS (Tag_Status_Array);
}
void Password_Verification(void)
{
	if(Msg_Variable[VALUE_INDEX]==PASSWORD)
	{
		 Edit_Mode_Page_Switch();
	}
}
void Event_Handler (uint8_t Tag_Log,uint8_t Status)
{
	Log[Tag_Log][1]=Status;
	Log[Tag_Log][2]=Tag[Tag_Log].Type;
	Log[Tag_Log][3]=APP_RTC.Years;
	Log[Tag_Log][4]=APP_RTC.Months;
	Log[Tag_Log][5]=APP_RTC.Days;
	Log[Tag_Log][6]=APP_RTC.Hours;
	Log[Tag_Log][7]=APP_RTC.Minutes;
	Log[Tag_Log][8]=APP_RTC.Seconds;
}


void Debug_M (void)
{
	Flash_Save_Data(Debug_Array);
}