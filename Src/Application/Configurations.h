/**************************************** THIS IS THE MAIN CONFIGURATIONS FILE *************************************/

/******************************************************************************************************************/
#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_
#include "main.h"


/**************************************** TEXT REPLACEMENT CONFIGURATIONS ********************************/

#define ANN_TAG_NUMBER             24

#define NON_TAG_INPUTS             7
#define TOTAL_INPUTS               ANN_TAG_NUMBER+NON_TAG_INPUTS+1
#define TAG_CODE                   ANN_TAG_NUMBER+1
#define VARIABLE                   0x06                      //Length of Msg (Variable type)
#define TEXT                       0x23                      //MUST SET !!! 25 character
#define PASSWORD                   1111

#define START_SAVE_ADDRESS         0x08019C00
#define INCREMENT_VALUE            0x20             //this value indicates the next value will be after 0x10 bytes.
/*******************************************************************************************************************/
#define TYPE_INDEX                 0x00
#define ADDRESS_INDEX              0x01
#define VALUE_INDEX                0x02
#define MSG_INDEX                  0x03
#define BYTE_SHIFT                 0x08

/*******************************************************************************************************************/

/***************************************** FIXED TEXT REPLACEMENT CONFIGURATIONS ***********************************/
/* Imp. note : list the number of available tags and after them the cmd buttons (Mute,Ack,Reset,Test) */
/* Array[TOTAL_INPUTS]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,Ack,Mute,Reset,Test,AC,DC} */
#define TAG_ONE              1
#define TAG_TWO              2
#define TAG_THREE            3
#define TAG_FOUR             4
#define TAG_FIVE             5
#define TAG_SIX              6
#define TAG_SEVEN            7
#define TAG_EIGHT            8
#define TAG_NINE             9
#define TAG_TEN              0xA
#define TAG_ELEVEN           0xB
#define TAG_TWELVE           0xC
#define TAG_THIRTEEN         0xD
#define TAG_FOURTEEN         0xE
#define TAG_FIFTEEN          0xF
#define TAG_SIXTEEN          0x10
#define TAG_SEVENTEEN        0x11
#define TAG_EIGHTEEN         0x12
#define TAG_NINETEEN         0x13
#define TAG_TWENTY           0x14
#define TAG_TWENTYONE        0x15
#define TAG_TWENTYTWO        0x16
#define TAG_TWENTYTHREE      0x17
#define TAG_TWENTYFOUR       0x18
#define TAG_TWENTYFIVE       
#define TAG_TWENTYSIX        
#define TAG_TWENTYSEVEN      
#define TAG_TWENTYEIGHT      
#define TAG_TWENTYNINE       
#define TAG_THIRTY           
#define TAG_THIRTYONE        
#define TAG_THIRTYTWO        

#define ACK                  0x19        //25               
#define MUTE                 0x1A				//26
#define RESET  							 0x1B
#define TEST 	               0x1C
#define AC                   0x1D
#define DC                   0x1E

#define PASSWORD_ADD         0x1F

#define ALARM_TRIP_ADD       0x90
/*************************************** RTC ***********************************************************************/
#define RTC_HOURS_ADD        0x400
#define RTC_MINUTES_ADD      0x410
#define RTC_SECONDS_ADD      0x420
/*******************************************************************************************************************/
#define NOT_OK               0
#define OK                   1
#define ALARM                1
#define TRIP                 2
/****************************************  MAIN TYPES  ****************************************************/

typedef struct 
{
	uint8_t Status;
	uint8_t Ack;
	uint8_t Mute;
	uint8_t Type;
	uint8_t Last_Status;
	//uint8_t History[100];                    //POD
}TAG;

/*******************************************************************************************************************/

#endif