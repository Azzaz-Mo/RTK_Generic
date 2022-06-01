#include "Configurations.h"
#include "Input_Scan_Interface.h"
#include "gpio.h"

/* Array[TOTAL_INPUTS]={1:24,Ack,Mute,Reset,Test,AC,DC} */
uint8_t Input_Array [TOTAL_INPUTS]={0};
uint8_t Target=0;
uint8_t Target_Local=0;
uint8_t Increment_Input=0;

uint8_t* Input_Scan (void)
{
//uint8_t Counter=INPUT_COUNTER;

	Input_Array[TYPE_INDEX]=TOTAL_INPUTS;
	Shift_Reg();                      																			  //Enable SH_LD Pin ---------- (POD)
	for (Increment_Input=1;Increment_Input<=TOTAL_INPUTS;Increment_Input++)
	{
       
			//send the number of the pin trigger the SH_REG for export Specific Bit mapping for non linear arrangement 
			
			Target=MAP(Increment_Input);   																			  
			Input_Array[Target]=Check(INPUT_PIN_SHIFT_REG);
			CLK_Input(); 
	
	}
	return Input_Array;
}

uint8_t Pin_Status=0;
uint8_t Check(uint8_t Check_Number)
{
	
	switch(Check_Number)
	{
		case 1 :
			Pin_Status=INPUT_1;
			break;
		case 2 :
			INPUT_2;
			break;
		case 3 :
			INPUT_3;
			break;
		case 4 :
			INPUT_4;
			break;
		case 5 :
			INPUT_5;
			break;
		case 6 :
			INPUT_6;
			break;
		case 7 :
			INPUT_7;
			break;
		case 8 :
			INPUT_8;
			break;
		case 9 :
			INPUT_9;
			break;
		case 10 :
			INPUT_10;
			break;
		case 11 :
			INPUT_11;
			break;
		case 12 :
			INPUT_12;
			break;
		case 13 :
			INPUT_13;
			break;
		case 14 :
			INPUT_14;
			break;
		case 15 :
			INPUT_15;
			break;
		case 16 :
			INPUT_16;
			break;
		case 17 :
			INPUT_17;
			break;
		case 18 :
			INPUT_18;
			break;
		case 19 :
			INPUT_19;
			break;
		case 20 :
			INPUT_20;
			break;
		case 21 :
			INPUT_21;
			break;
		case 22 :
			INPUT_22;
			break;
		case 23 :
			INPUT_23;
			break;
		case 24 :
			INPUT_24;
			break;
		case 25 :
			INPUT_25;
			break;
		case 26 :
			INPUT_26;
			break;
		case 27 :
			INPUT_27;
			break;
		case 28 :
			INPUT_28;
			break;
		case 29 :
			INPUT_29;
			break;
		case 30 :
			INPUT_30;
			break;
		case 31 :
			INPUT_31;
			break;
		case 32 :
			INPUT_32;
			break;
		
	}
return	Pin_Status;
}

uint8_t Increment_Clk=0;
uint8_t Shift_Reg (void)        //Shift register operation.
{
	SH_LD_Trigger();
}
void SH_LD_Trigger (void)
{
	SH_LD_Pin_LOW;
	Delay_ns ();      //delay 13 ns each clk X 10 = 130 ns
	SH_LD_Pin_HIGH;
}
void CLK_Input (void)
{ 
	CLK_Pin_HIGH;
	Delay_ns ();      //delay 13 ns each clk X 10 = 130 ns
	CLK_Pin_LOW;
}


uint8_t MAP(uint8_t Map_Number)
{

	switch (Map_Number)
	{
		case  S1 :
			Target_Local=1;
			break;
		case  S2 :
			Target_Local=2;
			break;
		case  S3 :
			Target_Local=3;
			break;
		case  S4 :
			Target_Local=4;
			break;
		case  S5 :
			Target_Local=5;
			break;
		case  S6 :
			Target_Local=6;
			break;
		case  S7 :
			Target_Local=7;
			break;
		case  S8 :
			Target_Local=8;
			break;
		case  S9 :
			Target_Local=9;
			break;
		case  S10:
			Target_Local=10;
			break;
		case  S11 :
			Target_Local=11;
			break;
		case  S12 :
			Target_Local=12;
			break;
		case   S13 :
			Target_Local=13;
			break;
		case   S14 :
			Target_Local=14;
			break;
		case   S15 :
			Target_Local=15;
			break;
		case   S16 :
			Target_Local=16;
			break;
		case   S17 :
			Target_Local=17;
			break;
		case   S18 :
			Target_Local=18;
			break;
		case   S19 :
			Target_Local=19;
			break;
		case   S20 :
			Target_Local=20;
			break;
		case   S21 :
			Target_Local=21;
			break;
		case   S22 :
			Target_Local=22;
			break;
		case  S23 :
			Target_Local=23;
			break;
		case  S24 :
			Target_Local=24;
			break;
		case  ACK_SH :
			Target_Local=ACK;
			break;
		case  MUTE_SH :
			Target_Local=MUTE;
			break;
		case  RESET_SH :
			Target_Local=RESET;
			break;
		case  AC_SH :
			Target_Local=AC;
			break;
		case  DC_SH :
			Target_Local=DC;
			break;
		default :
			Target_Local = 0;
	}
	return Target_Local;
}
void Delay_ns (void)
{ //delay 13 nano second each clock X 10 = 130 ns
	uint16_t i=0;
	for(i=0;i<20;i++)
	{}
}