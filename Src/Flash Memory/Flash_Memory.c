#include "Flash_Memory_Interface.h"
#include "Flash_Memory_Cfg.h"
#include "HMI_Interface.h"


uint16_t i=0;
	uint8_t saveddata[16]={0};
	uint32_t saveddata2[4]={0};
	uint32_t saveddata3[4]={0};
	uint8_t Load[16]={0};
	uint32_t save1=0;
		uint32_t save2=0;
		uint32_t save3=0;
		uint32_t save4=0;
		 uint32_t ck;
	uint32_t pk;
	uint8_t m;
	uint8_t r;
	uint8_t t;
		uint8_t Buffer[25]={0};
uint16_t place;
uint8_t	Save_To_Flash_Flag;
		typedef struct Event  
{
	uint8_t ID;
	uint8_t Status;
	uint8_t Type;
	uint8_t Year;
	uint8_t Month;
	uint8_t Day;
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
	
}Event;

uint32_t Send_Struct_To_Flash(Event *ptr);

	
	int volatile *  p_reg = (int *) 0x0801FC00;
	int volatile *  p_load = (int *) 0x0801FD7C;
	int volatile *  p_two = (int *) 0x0801A00C;
	int volatile *  p_3 = (int *) 0x0801A40C;
	int volatile *  p_4 = (int *) 0x0801A80C;
	int volatile *  p_5 = (int *) 0x0801AC0C;
	int volatile *  p_6 = (int *) 0x0801B00C;
	int volatile *  p_7 = (int *) 0x0801B40C;
	int volatile *  p_8 = (int *) 0x0801B80C;
	int volatile *  p_9 = (int *) 0x0801FC8C;
	int volatile *  p_10 = (int *) 0x0801C00C;
	int volatile *  p_11 = (int *) 0x0801C40C;
	int volatile *  p_12 = (int *) 0x0801C80C;
	int volatile *  p_13 = (int *) 0x0801CC0C;
	int volatile *  p_14 = (int *) 0x0801D00C;
	int volatile *  p_15 = (int *) 0x0801D40C;
	int volatile *  p_16 = (int *) 0x0801D80C;
	int volatile *  p_17 = (int *) 0x0801DC0C;
	int volatile *  p_18 = (int *) 0x0801E00C;
	int volatile *  p_19 = (int *) 0x0801E40C;
	int volatile *  p_20 = (int *) 0x0801E80C;
	int volatile *  p_21 = (int *) 0x0801EC0C;
	int volatile *  p_22 = (int *) 0x0801F00C;
	int volatile *  p_23 = (int *) 0x0801F40C;
	int volatile *  p_24 = (int *) 0x0801F80C;


/*  Getpage  Function  is  to catch the  address  of  specific  page  */               
static uint32_t GetPage(uint32_t Address)
{
  for (int indx=0; indx<128; indx++)
  {
	  if((Address < (0x08000000 + (1024 *(indx+1))) ) && (Address >= (0x08000000 + 1024*indx)))
	  {
		  return (0x08000000 + 1024*indx);
	  }
  }

  return -1;
}
/* function to write on byte of flash memory , used parameters (address of start page , name of the array which is pointer)*/
uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t * DATA_32,int Number_Of_Bytes)
{

	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;
	int sofar=0;

	int numberofwords = Number_Of_Bytes;


	  /* Unlock the Flash to enable the flash control register access *************/
	   HAL_FLASH_Unlock();

	   /* Erase the user Flash area*/

	  uint32_t StartPage = GetPage(StartPageAddress);
	  uint32_t EndPageAdress = StartPageAddress + numberofwords*4;
	  uint32_t EndPage = GetPage(EndPageAdress);

	   /* Fill EraseInit structure*/
	   EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	   EraseInitStruct.PageAddress = StartPage;
	   EraseInitStruct.NbPages     = ((EndPage - StartPage)/FLASH_PAGE_SIZE) +1;

	   if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
	   {
	     /*Error occurred while page erase.*/
		  return HAL_FLASH_GetError ();
	   }

	   /* Program the user Flash area word by word*/

	   while (sofar<numberofwords)
	   {
	     if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, StartPageAddress, DATA_32[sofar]) == HAL_OK)
	     {
	    	 StartPageAddress += 4;  // use StartPageAddress += 2 for half word and 8 for double word
	    	 sofar++;
	     }
	     else
	     {
	       /* Error occurred while writing data in Flash memory*/
	    	 return HAL_FLASH_GetError ();
	     }
	   }

	   /* Lock the Flash to disable the flash control register access (recommended
	      to protect the FLASH memory against possible unwanted operation) *********/
	   HAL_FLASH_Lock();
	   return 0;
}

void Erase (void)
{
	FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
  //FLASH_Erase Page
  while((FLASH->SR&FLASH_SR_BSY));
  FLASH->CR |= FLASH_CR_PER; //Page Erase Set
  FLASH->AR = Page_127; //Page Address
  FLASH->CR |= FLASH_CR_STRT; //Start Page Erase
  while((FLASH->SR&FLASH_SR_BSY));
  FLASH->CR &= ~FLASH_CR_PER; //Page Erase Clear
  //FLASH_Program HalfWord
  FLASH->CR |= FLASH_CR_PG;
  for(i=0; i<1024; i+=2)
  {
    while((FLASH->SR&FLASH_SR_BSY));
    *(__IO uint16_t*)(Page_127 + i) =2;
  }
  FLASH->CR &= ~FLASH_CR_PG;
  FLASH->CR |= FLASH_CR_LOCK;
}

void Save(uint8 * ptr) //function to save the incoming text and break after finish the last letter
{

	uint8_t i,y;
	for(i=0;i<25;i++)
	{
		Buffer[i]=*ptr;
		ptr++;
	}
	for(i=0;i<15;i++)
{
	saveddata[i]=0;
}
	
	for(i=0;i<25;i++)
	{
		y=i+7;
			if (Buffer[y]==0xFF)
		{break;}
		saveddata[i]=Buffer[y];
	}
	
			Save_To_Flash();
		
}

void Save_To_Flash(void)
  {
		save1=(saveddata[0])+(saveddata[1]<<8)+(saveddata[2]<<16)+(saveddata[3]<<24);
		saveddata2[0]=save1;
		save1=0;
		save2=(saveddata[4])+(saveddata[5]<<8)+(saveddata[6]<<16)+(saveddata[7]<<24);
		saveddata2[1]=save2;
		save2=0;
		save3=(saveddata[8])+(saveddata[9]<<8)+(saveddata[10]<<16)+(saveddata[11]<<24);
		saveddata2[2]=save3;
		save3=0;
		save4=(saveddata[12])+(saveddata[13]<<8)+(saveddata[14]<<16)+(saveddata[15]<<24);
		saveddata2[3]=save4;
		save4=0;
	place=(Buffer[4] << 8) + Buffer[5];
	switch(place)
 { 
		
		case 0x100:
			Flash_Write_Data( 0x08019C00 , saveddata2,4);
		break;
		case 0x110:
			Flash_Write_Data( 0x0801A000 , saveddata2,4);
		break;
		case 0x120:
			Flash_Write_Data( 0x0801A400 , saveddata2,4);
		break;
		case 0x130:
			Flash_Write_Data( 0x0801A800 , saveddata2,4);
		break;
		case 0x140:
			Flash_Write_Data( 0x0801AC00 , saveddata2,4);
		break;
		case 0x150:
			Flash_Write_Data( 0x0801B000 , saveddata2,4);
		break;
		case 0x160:
			Flash_Write_Data( 0x0801B400 , saveddata2,4);
		break;
		case 0x170:
			Flash_Write_Data( 0x0801B800 , saveddata2,4);
		break;
		case 0x180:
			Flash_Write_Data( 0x0801FC80 , saveddata2,4);
		break;
		case 0x190:
			Flash_Write_Data( 0x0801C000 , saveddata2,4);
		break;
		case 0x200:
			Flash_Write_Data( 0x0801C400 , saveddata2,4);
		break;
		case 0x210:
			Flash_Write_Data( 0x0801C800 , saveddata2,4);
		break;
		case 0x220:
			Flash_Write_Data( 0x0801CC00 , saveddata2,4);
		break;
		case 0x230:
			Flash_Write_Data( 0x0801D000 , saveddata2,4);
		break;
		case 0x240:
			Flash_Write_Data( 0x0801D400 , saveddata2,4);
		break;
		case 0x250:
			Flash_Write_Data( 0x0801D800 , saveddata2,4);
		break;
		case 0x260:
			Flash_Write_Data( 0x0801DC00 , saveddata2,4);
		break;
		case 0x270:
			Flash_Write_Data( 0x0801E000 , saveddata2,4);
		break;
		case 0x280:
			Flash_Write_Data( 0x0801E400 , saveddata2,4);
		break;
		case 0x290:
			Flash_Write_Data( 0x0801E800 , saveddata2,4);
		break;
		case 0x300:
			Flash_Write_Data( 0x0801EC00 , saveddata2,4);
		break;
		case 0x310:
			Flash_Write_Data( 0x0801F000 , saveddata2,4);
		break;
		case 0x320:
			Flash_Write_Data( 0x0801F400 , saveddata2,4);
		break;
		case 0x330:
			Flash_Write_Data( 0x0801F800 , saveddata2,4);
		break;
	}
}
	
void Load_Flash_Data (void)
{
	  p_load = (int *) 0x08019C0C;
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_load;
					p_load--;
			}
			Convert32_8();
			Send_Flash_Data(23);
			
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_two;
					p_two--;
			}
			Convert32_8();
			Send_Flash_Data(22);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_3;
					p_3--;
			}
			Convert32_8();
			Send_Flash_Data(21);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_4;
					p_4--;
			}
			Convert32_8();
			Send_Flash_Data(20);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_5;
					p_5--;
			}
			Convert32_8();
			Send_Flash_Data(19);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_6;
					p_6--;
			}
			Convert32_8();
			Send_Flash_Data(18);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_7;
					p_7--;
			}
			Convert32_8();
			Send_Flash_Data(17);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_8;
					p_8--;
			}
			Convert32_8();
			Send_Flash_Data(16);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_9;
					p_9--;
			}
			Convert32_8();
			Send_Flash_Data(15);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_10;
					p_10--;
			}
			Convert32_8();
			Send_Flash_Data(14);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_11;
					p_11--;
			}
			Convert32_8();
			Send_Flash_Data(13);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_12;
					p_12--;
			}
			Convert32_8();
			Send_Flash_Data(12);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_13;
					p_13--;
			}
			Convert32_8();
			Send_Flash_Data(11);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_14;
					p_14--;
			}
			Convert32_8();
			Send_Flash_Data(10);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_15;
					p_15--;
			}
			Convert32_8();
			Send_Flash_Data(9);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_16;
					p_16--;
			}
			Convert32_8();
			Send_Flash_Data(8);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_17;
					p_17--;
			}
			Convert32_8();
			Send_Flash_Data(7);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_18;
					p_18--;
			}
			Convert32_8();
			Send_Flash_Data(6);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_19;
					p_19--;
			}
			Convert32_8();
			Send_Flash_Data(5);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_20;
					p_20--;
			}
			Convert32_8();
			Send_Flash_Data(4);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_21;
					p_21--;
			}
			Convert32_8();
			Send_Flash_Data(3);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_22;
					p_22--;
			}
			Convert32_8();
			Send_Flash_Data(2);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_23;
					p_23--;
			}
			Convert32_8();
			Send_Flash_Data(1);
			for(i=1;i<5;i++)
			{
					saveddata3[4-i]=*p_24;
					p_24--;
			}
			Convert32_8();
			Send_Flash_Data(0);
			
			
}
void Send_Flash_Data (uint8_t target)
{
	switch(target)
	{
		case 23:
			r=0x01;
			t=0x00;
		break;
		case 22:
			r=0x01;
			t=0x10;
		break;
		case 21:
			r=0x01;
			t=0x20;
		break;
		case 20:
			r=0x01;
			t=0x30;
		break;
		case 19:
			r=0x01;
			t=0x40;
		break;
		case 18:
			r=0x01;
			t=0x50;
		break;
		case 17:
			r=0x01;
			t=0x60;
		break;
		case 16:
			r=0x01;
			t=0x70;
		break;
		case 15:
			r=0x01;
			t=0x80;
		break;
		case 14:
			r=0x01;
			t=0x90;
		break;
		case 13:
			r=0x02;
			t=0x00;
		break;
		case 12:
			r=0x02;
			t=0x10;
		break;
		case 11:
			r=0x02;
			t=0x20;
		break;
		case 10:
			r=0x02;
			t=0x30;
		break;
		case 9:
			r=0x02;
			t=0x40;
		break;
		case 8:
			r=0x02;
			t=0x50;
		break;
		case 7:
			r=0x02;
			t=0x60;
		break;
		case 6:
			r=0x02;
			t=0x70;
		break;
		case 5:
			r=0x02;
			t=0x80;
		break;
		case 4:
			r=0x02;
			t=0x90;
		break;
		case 3:
			r=0x03;
			t=0x00;
		break;
		case 2:
			r=0x03;
			t=0x10;
		break;
		case 1:
			r=0x03;
			t=0x20;
		break;
		case 0:
			r=0x03;
			t=0x30;
		break;
	}
  tx_buff=0xA5;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
  tx_buff=0x5A;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=0x13;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=0x82;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=r;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=t;
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[0];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[1];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[2];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[3];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[4];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[5];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[6];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[7];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[8];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[9];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[10];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[11];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[12];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[13];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[14];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	tx_buff=Load[15];
	HAL_UART_Transmit_IT(&huart1,&tx_buff,sizeof(tx_buff));
	Delay_Send_Flash();
	
	
}
void Convert32_8 (void)
{
		Load[0]=saveddata3[0];
		Load[1]=saveddata3[0]>>8;
		Load[2]=saveddata3[0]>>16;
		Load[3]=saveddata3[0]>>24;
	
		Load[4]=saveddata3[1];
		Load[5]=saveddata3[1]>>8;
		Load[6]=saveddata3[1]>>16;
		Load[7]=saveddata3[1]>>24;
		
		Load[8]=saveddata3[2];
		Load[9]=saveddata3[2]>>8;
		Load[10]=saveddata3[2]>>16;
		Load[11]=saveddata3[2]>>24;
		
		Load[12]=saveddata3[3];
		Load[13]=saveddata3[3]>>8;
		Load[14]=saveddata3[3]>>16;
		Load[15]=saveddata3[3]>>24;
	
}

uint8_t *Get_Tag (uint8_t Tag_Number)
{
	
	uint8_t *Return_Value=0;
	Return_Value=(uint8_t *)((0x08019800)+(Tag_Number*0x400));            //return the address of the first letter of the tag since it's separated by 1024 byte = 0x400.
	return Return_Value;
}

void Delay_Send_Flash(void)
{uint16_t i=0;
	for(i=0;i<10000;i++)         //8518 is the number of delay
	{}
}
/* sending data from app to flash module */ 
uint32_t* Flash_Counter_Ptr_Address=(uint32_t *)COUNTER_ADDRESS; 
uint32_t Send_Struct_To_Flash(Event *ptr)
{
	uint32_t  Counter_Address=*Flash_Counter_Ptr_Address;       //fetch data from Flash to Local Varibale.
	uint32_t First_32=0;
	uint32_t Second_32=0;
	

	
	uint8_t ID=ptr->ID;                                //dispatching
	uint8_t Type=ptr->Type;                            //dispatching
	uint8_t Status=ptr->Status;                        //dispatching
	uint8_t Year=ptr->Year;                            //dispatching
	uint8_t Month=ptr->Month;                          //dispatching
	uint8_t Day=ptr->Day;                              //dispatching
	uint8_t Hour=ptr->Hour;                            //dispatching
	uint8_t minute=ptr->Minute;                        //dispatching
	uint8_t Second=ptr->Second;                        //dispatching
  
	
	First_32=Convert_8_To_32(ID,Status,Year,Month);    //here we call a function the returns a 32-bit variable for each byte variable.
	Second_32=Convert_8_To_32(Day,Hour,minute,Second);
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Counter_Address,First_32);             
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Counter_Address+0x04,Second_32);
	HAL_FLASH_Lock();
	Counter_Address=Counter_Address+0x08;              //4 byteX2 increment ** to be saved for the next process.

	return (Counter_Address);
}
uint32_t Convert_8_To_32(uint8 First,uint8 Second,uint8 Third , uint8 Fourth)
{
	uint32_t Process=0;
	Process=First;
	Process=Process<<8;
	Process|=Second;
	Process=Process<<8;
	Process|=Third;
	Process=Process<<8;
	Process|=Fourth;
	
	return Process;
}
