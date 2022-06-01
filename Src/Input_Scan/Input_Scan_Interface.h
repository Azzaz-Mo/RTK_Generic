#ifndef INPUT_SCAN_INTERFACE_H_
#define INPUT_SCAN_INTERFACE_H_
#include "main.h"
#include "Input_Scan_Cfg.h"

uint8_t* Input_Scan (void);
uint8_t Check(uint8_t Check_Number);
uint8_t Shift_Reg (void);
uint8_t MAP(uint8_t Map_Number);
void Delay_ns (void);
void CLK_Input (void);
void SH_LD_Trigger (void);









#endif