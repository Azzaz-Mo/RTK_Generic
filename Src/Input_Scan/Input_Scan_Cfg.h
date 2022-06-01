/**************************************** USER CONFIGURATIONS ************************************************/

/*************************************************************************************************************/
/**************************************** INTERNAL CONFIGURATIONS ********************************************/

#define     HIGH                     1
#define     LOW                      0

/**************************************** SHIFT REGISTER ARRANGEMENT (MAPPING) **************************************/

#define     CLK_Pin_HIGH                 HAL_GPIO_WritePin(SH_CLK_GPIO_Port,SH_CLK_Pin,HIGH);                 
#define     CLK_Pin_LOW                  HAL_GPIO_WritePin(SH_CLK_GPIO_Port,SH_CLK_Pin,LOW);

#define     SH_LD_Pin_HIGH               HAL_GPIO_WritePin(SH_LD_GPIO_Port,SH_LD_Pin,HIGH);
#define     SH_LD_Pin_LOW                HAL_GPIO_WritePin(SH_LD_GPIO_Port,SH_LD_Pin,LOW);

#define     SHIFT_REG_NUMBER             4
#define     SHIFT_REG_CLK                SHIFT_REG_NUMBER*8
/* Arrange According to the arrangement of Shift Reg. frame From LSB to MSB*/
#define     S1                           28                                          
#define     S2                           27
#define     S3                           26
#define     S4                           25
#define     S5                           32
#define     S6                           31
#define     S7                           30
#define     S8                           29
#define     S9                           20                           
#define     S10                          19
#define     S11                          18
#define     S12                          17
#define     S13                          24
#define     S14                          23
#define     S15                          22
#define     S16                          21
#define     S17                          12
#define     S18                          11
#define     S19                          10
#define     S20                          9
#define     S21                          16
#define     S22                          15
#define     S23                          14
#define     S24                          13
#define     S25
#define     S26
#define     S27
#define     S28
#define     S29
#define     S30
#define     S31
#define     S32

#define     AC_SH                           4
#define     DC_SH                           3
#define     MUTE_SH                         8  
#define     ACK_SH                          1 
#define     RESET_SH                        2
#define     NOT_CONNECTED                   5 //5,6,7 Not connected   

/*************************************************************************************************************/
#define     INPUT_PIN_SHIFT_REG          1                         //mention the input number
/**************************************** INPUT CONFIGURATIONS ********************************************/
#define     INPUT_1                      HAL_GPIO_ReadPin(SH_OUT_GPIO_Port,SH_OUT_Pin);     
#define     INPUT_2                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_3                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_4                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_5                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_6                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_7                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_8                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_9                      HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_10                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_11                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_12                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_13                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_14                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_15                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_16                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_17                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_18                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_19                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_20                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_21                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_22                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_23                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_24                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_25                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_26                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_27                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_28                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_29                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_30                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_31                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   
#define     INPUT_32                     HAL_GPIO_ReadPin(INPUT1_GPIO_Port,INPUT1_Pin);   


