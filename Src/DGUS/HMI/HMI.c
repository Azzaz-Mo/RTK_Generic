#include "HMI_Interface.h"
#include "HMI_Cfg.h"
#include "Configurations.h"

//#include "Flash_Memory_Interface.h"

	uint8_t	 tx_buff=0;
	uint16 iteration;
	uint8_t rx_buff[35]={0};
uint8_t x=0;
	void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  x=3;
}
void HMI_Init(void)
{
	HAL_UART_Receive_DMA(&huart1,rx_buff,sizeof(rx_buff));
}
/* THIS FUNCTION IS RESPONSIBLE FOR SEARCHIN FOR THE MSG AND EXTRACT IT FROM BUFFER*/ 
	uint8_t rx_array[MAX_SIZE+MSG_STD]={0};
	uint8_t Msg_Status=0;
	uint8_t Msg_Length=0;
	uint8_t Msg_Finished=0;
	uint16_t Msg_HMI[MAX_SIZE]={0};
	uint8_t Increment_HMI=NOT_OK;
	uint8_t Saved_Index=NOT_OK;
	uint8_t MSG_Intro_L=NOT_OK;
	uint8_t Index=NOT_OK;
//Simple Frame A5 5A 06 82 00 02 01 00 40
//Text Frame   A5 5A 08 82 01 00 02 0A 0B 0C 0D ....etc	 

uint16_t* HMI_Check_Msg(void)
{

	for(Increment_HMI=MSG_INTRO_H_INDEX;Increment_HMI<MAX_SIZE;Increment_HMI++)
{
	
		if(rx_buff[Increment_HMI]==MSG_INTRO_H)
		{		
			HAL_Delay(1);
			Index=Increment_HMI;
			Safety_Condition();
			
			break;
		}
		
}		
			
			if(rx_buff[Index]==MSG_INTRO_L)
			{
							Safety_Condition();
							Msg_Status=rx_buff[Index];
							Msg_HMI[TYPE_INDEX]=Msg_Status;
							Safety_Condition();
							Safety_Condition();
							Msg_HMI[ADDRESS_INDEX]=rx_buff[Index];
							Msg_HMI[ADDRESS_INDEX]=Msg_HMI[ADDRESS_INDEX]<<BYTE_SHIFT;
							Safety_Condition();
							Msg_HMI[ADDRESS_INDEX]|=rx_buff[Index];
							Safety_Condition();
							Msg_Length=rx_buff[Index];                 //Indicates the length of the data.                           
							Safety_Condition();
							if(Msg_Length>1)                 //since if the msg was variable , so this byte will be 1 , otherwise it's the number of text bytes.
							{
								Msg_HMI[TYPE_INDEX]=Msg_Length;
									for (Increment_HMI=0;Increment_HMI<Msg_Length;Increment_HMI++)
								{
									Msg_HMI[VALUE_INDEX+Increment_HMI]=rx_buff[Index];
									Safety_Condition();
								}
							}
							else
							{
								Msg_HMI[VALUE_INDEX]=rx_buff[Index];
								Msg_HMI[VALUE_INDEX]=Msg_HMI[VALUE_INDEX]<<BYTE_SHIFT;
								Safety_Condition();
								Msg_HMI[VALUE_INDEX]|=rx_buff[Index];
							}
								RESET_Buff();
								MSG_Intro_L=NOT_OK;
								Index=NOT_OK;
				}
			
				
				
			else
			{
				//wrong frame
			}
			
			
	return (Msg_HMI);
}
void RESET_Buff(void)
{
	rx_buff[0]=NOT_OK;
	rx_buff[1]=NOT_OK;
	rx_buff[2]=NOT_OK;
	rx_buff[3]=NOT_OK;
	rx_buff[4]=NOT_OK;
	rx_buff[5]=NOT_OK;
	rx_buff[6]=NOT_OK;
	rx_buff[7]=NOT_OK;
	rx_buff[8]=NOT_OK;
	rx_buff[9]=NOT_OK;
	rx_buff[10]=NOT_OK;
	rx_buff[11]=NOT_OK;
	rx_buff[12]=NOT_OK;
	rx_buff[13]=NOT_OK;
	rx_buff[14]=NOT_OK;
	rx_buff[15]=NOT_OK;
	rx_buff[16]=NOT_OK;
	rx_buff[17]=NOT_OK;
	rx_buff[18]=NOT_OK;
	rx_buff[19]=NOT_OK;
	rx_buff[20]=NOT_OK;
	rx_buff[21]=NOT_OK;
	rx_buff[22]=NOT_OK;
	rx_buff[23]=NOT_OK;
	rx_buff[24]=NOT_OK;
	rx_buff[25]=NOT_OK;
	rx_buff[26]=NOT_OK;
	rx_buff[27]=NOT_OK;
	rx_buff[28]=NOT_OK;
	rx_buff[29]=NOT_OK;
	rx_buff[30]=NOT_OK;
	rx_buff[31]=NOT_OK;
	rx_buff[32]=NOT_OK;
	rx_buff[33]=NOT_OK;
	rx_buff[34]=NOT_OK;
		
}
void Safety_Condition (void)
{
	/*********** Safety Condition ***********/
			if(Index==MAX_SIZE)
			{
				Index=0;
			}
			else
			{
				Index++;
			}
			/****************************************/
}
//	if (Save_Flag==OK)
//	{
//		Save_Flag=NOT_OK;
//		//Save(rx_array);     //save the text to flash memory
//		for(iteration=0;iteration<25;iteration++)
//		{
//			rx_array[iteration]=0;
//		}
//	}
//	if(Serial_Event_Flag==OK)
//	{
//		Serial_Event_Flag=NOT_OK;
//		Send_Normal();
//		serial1Event();     // function to get off address and value of the action on HMI
//		if (Address==PASSWORD_ADD)  //Password Address to check
//				{
//					if (Value==PASSWORD)
//					{
//						Address=0;            //reset any previous data 
//						Value=0;              //reset any previous data 
//						DGUS_Page_Switch ();  //change the page to edit mode page.
//						
//					}
//					else
//					{
//						Address=0;              //reset any previous data 
//						Value=0;               //reset any previous data 
//					}
//				}
//		
//	}

//	}
void DGUS_SendText (uint8_t* Ptr)
{	
	uint8_t Array_Send[37]={0};
	uint8_t Length=Ptr[0];
	
	Array_Send[0]=0xA5;
	Array_Send[1]=0x5A;
	Array_Send[2]=Length;
	Array_Send[3]=0x82;
	Array_Send[4]=Ptr[1];
	Array_Send[5]=Ptr[2];
	for(Increment_HMI=0;Increment_HMI<32;Increment_HMI++)
	{
		Array_Send[Increment_HMI+6]=Ptr[Increment_HMI+3];
	}
	
	for(Increment_HMI=0;Increment_HMI<37;Increment_HMI++)
	{
		HAL_UART_Transmit_IT(&huart1,&Array_Send[Increment_HMI],sizeof(Array_Send[Increment_HMI]));
		Delay_Send();
	}
	
	
}

    void DGUS_Beep(uint16_t bTime) // Beep generate bTime*10ms
{ 
	uint8_t Array_Send[6]={0};
	uint8_t i=0;
  Array_Send[0]=0xA5; 
	Array_Send[1]=0x5A;
	Array_Send[2]=0x03;
	Array_Send[3]=0x80;
	Array_Send[4]=0x02;
	Array_Send[5]=bTime;
	for(i=0;i<6;i++)
	{
		HAL_UART_Transmit_IT(&huart1,&Array_Send[i],sizeof(Array_Send[i]));
		Delay_Send();
		
	}
}


void DGUS_SendVal(int iAdr, int iVal) //Send iVal for VP= iAdr to DGUS
{
  uint8_t bAdrL, bAdrH, bValL, bValH;
  bAdrL = iAdr & 0xFF;
  bAdrH = (iAdr >> 8) & 0xFF;
  bValL = iVal & 0xFF;
  bValH = (iVal >> 8) & 0xFF;
	uint8_t Array_Send[8]={0};
	uint8_t i=0;
  Array_Send[0]=0xA5;
	
  Array_Send[1]=0x5A;
	Array_Send[2]=0x05;
	Array_Send[3]=0x82;
	Array_Send[4]=bAdrH;
	Array_Send[5]=bAdrL;
	Array_Send[6]=bValH;
	Array_Send[7]=bValL;
	for(i=0;i<8;i++)
	{
		HAL_UART_Transmit_IT(&huart1,Array_Send,sizeof(Array_Send));
		Delay_Send();
		
	}
}


void DGUS_Page_Switch (void) //Send iVal for VP= iAdr to DGUS
{
  tx_buff=0xA5;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
  tx_buff=0x5A;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
  tx_buff=0x04;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
  tx_buff=0x80;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
  tx_buff=0x03;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
	tx_buff=0x00;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	HAL_Delay(1);
  tx_buff=0x03;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
  HAL_Delay(1);
}

void Send_Normal (void)
{
	for(iteration=0;iteration<9;iteration++)
	{
	//	rx_array2[iteration]=rx_array[iteration];
	}
}
void Delay_Send(void)
{uint16_t i=0;
	for(i=0;i<8000;i++)         //8518 is the number of delay
	{}
}