#include "bsp_uart.h"
#include "bsp_gpio.h" 
#include "ymodem.h"
#include "shell_port.h"
#include "commond.h"
#pragma import(__use_no_semihosting)             
               
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       

void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);   
	USART1->DR = (u8) ch;      
	return ch;
}

u8 USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));	

void uart_init(GPIO_TypeDef* GPIOx,USART_TypeDef* USARTx,uart_config_t uart_config,gpio_config_t gpio_config)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(gpio_config.RCC_GPIOx,ENABLE); 
	RCC_APB2PeriphClockCmd(uart_config.RCC_USARTx,ENABLE);
 
	GPIO_PinAFConfig(GPIOx,uart_config.PinSource1,uart_config.gpio_af); 
	GPIO_PinAFConfig(GPIOx,uart_config.PinSource2,uart_config.gpio_af); 
	
	gpio_out_in_init(GPIOx,gpio_config);
	
	USART_InitStructure.USART_BaudRate = uart_config.bound;
	USART_InitStructure.USART_WordLength = uart_config.wordlength;
	USART_InitStructure.USART_StopBits = uart_config.stopbit;
	USART_InitStructure.USART_Parity = uart_config.parity;
	USART_InitStructure.USART_HardwareFlowControl = uart_config.hwflowcontrol;
	USART_InitStructure.USART_Mode = uart_config.mode;	
	USART_Init(USARTx, &USART_InitStructure); 
	 
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USARTx, ENABLE); 

	NVIC_InitStructure.NVIC_IRQChannel = uart_config.irqchannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=uart_config.irqpreemption;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =uart_config.irqSub;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
}


extern Buffer recvBuf;

void USART1_IRQHandler(void)                
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		Res =USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		if(boot_param.boot_sta == star_ymodem)
		{
			recvBuf.data[recvBuf.len++] = Res;
			TIM5->CNT = 0;
			TIM_Cmd(TIM5, ENABLE);	
		}
		else
		{
			if(Res == 0X0D)
				boot_param.boot_sta = hold_boot;
			shellHandler(&shell, Res);
		}
	} 
} 

void usart_SendByte(uint8_t ch)
{
	USART_SendData(USART1,ch);
		
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
}
