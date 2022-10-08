#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "bsp_gpio.h"


#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2

#define KEY0_PRES   1
#define KEY1_PRES	2
#define KEY2_PRES	3

void key_init(void);
u8 key_scan(void);
#endif
