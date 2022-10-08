#include "stdio.h"
#include "shell_port.h"
#include "bsp_uart.h"

Shell shell;

char shell_buffer[512];

void user_shell_write(const char ch)
{
	USART_SendData(USART1,ch);
}


void user_shell_init(void)
{
	shell.write = user_shell_write;
	shellInit(&shell,shell_buffer,512);
}



