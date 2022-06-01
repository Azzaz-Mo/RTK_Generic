#include "Configurations.h"
#include "Flash_Interface.h"
#include "Flash_Cfg.h"

/* This function is responsible for allocating specific text into flash (Configurable) */
uint8_t Length=0;
uint16_t Address=0;
uint32_t Location=0;
uint32_t Offset_Value=0;
uint8_t Increment_Flash=0;
uint16_t Test_Flash=0x5555;
uint32_t Buffer[256]={0};
uint32_t* Buffer_Ptr=0;
uint8_t Read_Ptr_16bits[TEXT+1]={0};
uint8_t Flash_Increment_2=2;
uint8_t Temp=0;
void Flash_Save_Data (uint16_t * Read_Ptr)
{
	Length=Read_Ptr[0];
	Address=Read_Ptr[1];
	Location=Load_Address_Location(Address);        //POD , since the addresses map should be in DGUS module not Flash
	for(Increment_Flash=2;Increment_Flash<(Length+2);Increment_Flash=Increment_Flash+2)
	{
		Temp=Read_Ptr[Increment_Flash];
		Read_Ptr[Flash_Increment_2]=(Read_Ptr[Increment_Flash+1]);
		Read_Ptr[Flash_Increment_2]=Read_Ptr[Increment_Flash+1]<<8;
		Read_Ptr[Flash_Increment_2]|=Temp;
		Flash_Increment_2++;
	}
	Length=Flash_Increment_2;
	Save_Flash_Into_Buffer();
	Erase();
	HAL_FLASH_Unlock();
	for(Increment_Flash=0;Increment_Flash<((Length/2)+1);Increment_Flash++)
	{
		HAL_Delay(50);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,Location+(0x2*Increment_Flash),Read_Ptr[Increment_Flash+2]);     
	}
	Save_Buffer_Into_Flash();
	HAL_FLASH_Lock();
}


uint8_t Read_Data[TEXT+1]={0};
uint8_t Tag_Counter=1;

uint8_t * Flash_Load_Data_2 (uint16_t Tag_ID)
{
	
	uint32_t Tag_Address=0;
	Tag_Address=Load_Address_Location(Tag_ID);
	uint8_t* Read_Crusor_Ptr=(uint8_t*)Tag_Address;
	
	for(Increment_Flash=1;Increment_Flash<=25;Increment_Flash++)
	{
		if (*Read_Crusor_Ptr!=0xFF)
		{
			Read_Data[Tag_Counter]=Read_Crusor_Ptr[Tag_Counter-1];
			Tag_Counter++;
		}
		else
		{
			//do nothing
		}
	}
	Read_Data[0]=Tag_Counter;
	return(Read_Data);
}
//0x08019C00 TAG_ONE old
//0x0801F800 TAG_TWENTYFOUR old
uint32_t Load_Address_Location (uint16_t Address_Location)
{
	switch (Address)
	{
		case LOCATION_1 :
			Offset_Value=INCREMENT_VALUE*0;
			break;
		case LOCATION_2 :
			Offset_Value=INCREMENT_VALUE*1;
			break;
		case LOCATION_3 :
			Offset_Value=INCREMENT_VALUE*2;
			break;
		case LOCATION_4 :
			Offset_Value=INCREMENT_VALUE*3;
			break;
		case LOCATION_5 :
			Offset_Value=INCREMENT_VALUE*4;
			break;
		case LOCATION_6 :
			Offset_Value=INCREMENT_VALUE*5;
			break;
		case LOCATION_7 :
			Offset_Value=INCREMENT_VALUE*6;
			break;
		case LOCATION_8 :
			Offset_Value=INCREMENT_VALUE*7;
			break;
		case LOCATION_9 :
			Offset_Value=INCREMENT_VALUE*8;
			break;
		case LOCATION_10 :
			Offset_Value=INCREMENT_VALUE*9;
			break;
		case LOCATION_11 :
			Offset_Value=INCREMENT_VALUE*10;
			break;
		case LOCATION_12 :
			Offset_Value=INCREMENT_VALUE*11;
			break;
		case LOCATION_13 :
			Offset_Value=INCREMENT_VALUE*12;
			break;
		case LOCATION_14 :
			Offset_Value=INCREMENT_VALUE*13;
			break;
		case LOCATION_15 :
			Offset_Value=INCREMENT_VALUE*14;
			break;
		case LOCATION_16 :
			Offset_Value=INCREMENT_VALUE*15;
			break;
		case LOCATION_17 :
			Offset_Value=INCREMENT_VALUE*16;
			break;
		case LOCATION_18 :
			Offset_Value=INCREMENT_VALUE*17;
			break;
		case LOCATION_19 :
			Offset_Value=INCREMENT_VALUE*18;
			break;
		case LOCATION_20 :
			Offset_Value=INCREMENT_VALUE*19;
			break;
		case LOCATION_21 :
			Offset_Value=INCREMENT_VALUE*20;
			break;
		case LOCATION_22 :
			Offset_Value=INCREMENT_VALUE*21;
			break;
		case LOCATION_23 :
			Offset_Value=INCREMENT_VALUE*22;
			break;
		case LOCATION_24 :
			Offset_Value=INCREMENT_VALUE*23;
			break;
		
	}
	return (LOCATION_1_PLACE+Offset_Value);
}

void Erase (void)
{
	static FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PAGEError;
	HAL_FLASH_Unlock();
	
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	   EraseInitStruct.PageAddress = START_SAVE_ADDRESS;
	   EraseInitStruct.NbPages     = 1;
	
HAL_FLASHEx_Erase(&EraseInitStruct,&PAGEError);

}
void Save_Flash_Into_Buffer(void)
{
 Buffer_Ptr= (uint32_t *)START_SAVE_ADDRESS;
	for (Increment_Flash=0;Increment_Flash<255;Increment_Flash++)
	{
		if(Buffer_Ptr[Increment_Flash]!=0xFFFFFFFF)
		{
			Buffer[Increment_Flash]=Buffer_Ptr[Increment_Flash];
		}
	}
}
void Save_Buffer_Into_Flash(void)
{
	Buffer_Ptr=(uint32_t *) START_SAVE_ADDRESS;
	for (Increment_Flash=0;Increment_Flash<255;Increment_Flash++)
	{
		HAL_Delay(1);
		if (Buffer[Increment_Flash]>0)
		{
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,START_SAVE_ADDRESS+(Increment_Flash*4),Buffer[Increment_Flash]);
		}
	}
	
}
