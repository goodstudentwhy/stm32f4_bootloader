#ifndef __BSP_UART_H
#define __BSP_UART_H
#include "sys.h"
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "bsp_gpio.h" 

enum
{
	_1200_bound = 1200,
	_2400_bound = 2400,
	_4800_bound = 4800,
	_9600_bound = 9600,
	_14400_bound = 14400,
	_19200_bound = 19200,
	_38400_bound = 38400,
	_57600_bound = 57600,
	_115200_bound = 115200,
	_128000_bound = 128000,
};

typedef struct
{
	uint32_t RCC_USARTx			:32;
	uint32_t bound 				:32;
	uint16_t wordlength 		:16;
	uint16_t stopbit			:16;
	uint16_t parity				:12;
	uint16_t hwflowcontrol		:12;
	uint16_t mode				:4; 
	uint8_t  PinSource1			:8;	
	uint8_t  PinSource2			:8;	
	uint8_t  gpio_af			:8;
	uint8_t  irqchannel			:8; 
	uint8_t  irqpreemption		:8; 
	uint8_t	 irqSub				:8; 
}uart_config_t;


#define USART_REC_LEN  			120*1024  	
	  	
extern u8 USART_RX_BUF[USART_REC_LEN]; 			

void uart_init(GPIO_TypeDef* GPIOx,USART_TypeDef* USARTx,uart_config_t uart_config,gpio_config_t gpio_config);
void usart_SendByte(uint8_t ch);
#endif
