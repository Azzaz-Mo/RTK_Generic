/******************************************* HERE WE CONFIGURE LOW DRIVER **************************************/
#include "Platform_Types.h"
/******************************************* FIXED CONFIGURATIONS **********************************************/
//Simple Frame A5 5A 06 82 "00 02" 01 "00 40"
//Text Frame A5 5A 0x 82 00 00 00 00 00 00 00 ....etc	 
/***************************************************************************************************************/
#define MSG_STD                    0x03            //this is the total fixed part of the frame (A5,5A,xx).
#define MSG_INTRO_H_INDEX          0x00
#define MSG_INTRO_L_INDEX          0x01
#define MSG_LENGTH_INDEX           0x02
#define MSG_ADDRESS_H_INDEX        0x04           
#define MSG_ADDRESS_L_INDEX        0x05
#define MSG_VALUE_H_INDEX          0x07
#define MSG_VALUE_L_INDEX					 0x08


/******************************************* VARIABLE CONFIGURATIONS **********************************************/
/***************************************************************************************************************/
#define MSG_INTRO_H      0xA5
#define MSG_INTRO_L      0x5A


#define MAX_SIZE         0x23                      //MAX_SIZE MUST BE THE MAX of TEXT.

#define PASSWORD_ADD     0x99
#define PASSWORD         1111