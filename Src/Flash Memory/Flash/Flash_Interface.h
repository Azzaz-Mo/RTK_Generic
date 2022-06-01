#ifndef FLASH_INTERFACE_H_
#define FLASH_INTERFACE_H_

#include "Flash_Cfg.h"
#include "Configurations.h"

void Flash_Save_Data (uint16_t * Read_Ptr);
uint32_t Load_Address_Location (uint16_t Address_Location);
void Erase (void);
void Save_Flash_Into_Buffer(void);
void Save_Buffer_Into_Flash(void);
uint8_t * Flash_Load_Data_2 (uint16_t Tag_ID);












#endif