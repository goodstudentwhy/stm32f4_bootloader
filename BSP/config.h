#ifndef __CONFIG_H
#define __CONFIG_H

#include "sys.h"

#define _BOOT_VERSION "1.0.0"


/******LED配置*******/
#define READ_LED_GPIO_CONFIG					\
{																			\
	RCC_AHB1Periph_GPIOF,								\
	GPIO_Pin_9,		/*pin9引脚*/					\
	GPIO_Mode_OUT,	/*输出模式*/				\
	GPIO_OType_PP,	/*推挽模式*/				\
	GPIO_Speed_100MHz, /*速度100MHZ*/		\
	GPIO_PuPd_UP,	/*上拉模式*/					\
}

/******定时器3配置*******/
#define TIME3_CONFIG					\
{															\
	999,												\
	83,													\
	TIM_CounterMode_Up,					\
	TIM_CKD_DIV1,								\
	TIM3_IRQn,									\
	1,													\
	3,													\
	ENABLE,							\
}

/******定时器5配置*******/
#define TIME5_CONFIG					\
{															\
	9999,												\
	83,													\
	TIM_CounterMode_Up,					\
	TIM_CKD_DIV1,								\
	TIM5_IRQn,									\
	1,													\
	3,													\
	DISABLE,					\
}

/******串口1GPIO配置*******/
#define UART1_GPIO_CONFIG			\
{															\
	RCC_AHB1Periph_GPIOA,				\
	GPIO_Pin_9|GPIO_Pin_10,			\
	GPIO_Mode_AF,								\
	GPIO_OType_PP,							\
	GPIO_Speed_50MHz,						\
	GPIO_PuPd_UP,								\
}

/******串口1配置*******/
#define UART1_CONFIG							\
{																	\
	RCC_APB2Periph_USART1,					\
	_115200_bound,									\
	USART_WordLength_8b,						\
	USART_StopBits_1,								\
	USART_Parity_No,								\
	USART_HardwareFlowControl_None,	\
	USART_Mode_Rx | USART_Mode_Tx,	\
	GPIO_PinSource9,								\
	GPIO_PinSource10,								\
	GPIO_AF_USART1,									\
	USART1_IRQn,										\
	3,															\
	3,															\
}

/******按键配置*******/
#define KEY_CONFIG													\
{																						\
	RCC_AHB1Periph_GPIOE,											\
	GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4,					\
	GPIO_Mode_IN,															\
	0,																				\
	GPIO_Speed_100MHz,												\
	GPIO_PuPd_UP,															\
}



#endif

