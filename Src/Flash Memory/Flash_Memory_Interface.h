#ifndef FLASH_MEMORY_INTERFACE_H_
#define FLASH_MEMORY_INTERFACE_H_
#include "main.h"
//#include "Main_Cfg.h"
#include "usart.h"


void Save_To_Flash (void);
void Save (uint8_t *);
void	Load_Flash_Data(void);
void Send_Flash_Data (uint8_t);
void Convert32_8 (void);
uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t * DATA_32,int Number_Of_Bytes);
extern uint8_t	Save_To_Flash_Flag;
uint8_t *Get_Tag (uint8_t Tag_Number);
void Delay_Send_Flash(void);
uint32_t Convert_8_To_32(uint8_t First,uint8_t second,uint8_t third , uint8_t fourth);















#endif