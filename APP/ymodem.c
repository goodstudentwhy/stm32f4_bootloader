#include "ymodem.h"
#include "string.h"
#include "bsp_uart.h"
#include "stmflash.h"
#include "sys.h"
#include "stdio.h"
#include "IAP.h"
#include "delay.h"
#include "shell_port.h"

YModem ymodem = {WAIT_ENTER_SYSTEM, 0, 0, FLASH_APP1_ADDR, 0, {0}};
ProcessStatus process;

void ymodem_ack(void) 
{
	usart_SendByte(USART1,ACK);
}

void ymodem_nack(void) 
{
	usart_SendByte(USART1,NAK);
}

void ymodem_c(void) 
{
	usart_SendByte(USART1,CRC16);
}

void set_ymodem_status(ProcessStatus process) 
{
	ymodem.process = process;
}

ProcessStatus get_ymodem_status(void) 
{
	ProcessStatus process = ymodem.process;
	return process;
}

/**
 *名称：ymodem_recv
 *功能：ymodem协议接收函数
 *输入：
	@Buffer：串口接收到的数据和长度
**/
void ymodem_recv(Buffer *p) 
{
	uint8_t type = p->data[0];
	static int i = 0;
	static u32 USART_RX_CNT = 0;
	switch (ymodem.status) 
	{
		case 0:
			if (type == SOH || type == STX) 
			{
				ymodem.process = BUSY;
				ymodem.addr = FLASH_APP1_ADDR;
				ymodem_ack();
				delay_us(10);
				ymodem_c();
				ymodem.status++;
			}
			break;
		case 1:
			if (type == SOH || type == STX) 
			{
				if (type == SOH)
				{
//					load_buf(&p->data[3],128);
					memcpy(USART_RX_BUF+(i*PACKET_SIZE_128),&p->data[3],PACKET_SIZE_128);
					i++;
					USART_RX_CNT += 128;
				}
				else 
				{
//					load_buf(&p->data[3],1024);
					memcpy(USART_RX_BUF+(i*PACKET_SIZE_1024),&p->data[3],PACKET_SIZE_1024);
					i++;
					USART_RX_CNT += 1024;
				}
				ymodem_ack();
			}
			else if (type == EOT) 
			{
				ymodem_nack();
				ymodem.status++;
			}
			else 
				ymodem.status = 0;
			break;
		case 2:
			if (type == EOT) 
			{
				ymodem_ack();
				delay_us(10);
				ymodem_c();
				delay_us(10);
				ymodem.status++;
			}
			break;
		case 3:
			if (type == SOH) 
			{
				ymodem_ack();
				ymodem.status = 0;
				ymodem.process = UPDATE_SUCCESS;
				iap_write_appbin(ymodem.addr, USART_RX_BUF, USART_RX_CNT);
			}
	}
	p->len = 0;
	memset(p->data,0,sizeof(p->data));
}

/**
 *名称：ymodem_task
 *功能：ymodem循环主函数
**/
void ymodem_task(void)
{
	static int cnt = 0,c_delay = 0;
	process = get_ymodem_status();
	switch (process) 
	{
		case WAIT_ENTER_SYSTEM:
			cnt++;
			if (cnt >= 500) 
			{
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)
				{
					if (!iap_load_app(FLASH_APP1_ADDR)) 
					{
						printf("APP固件不存在\r\n");
						cnt = 0;
						set_ymodem_status(WAIT_ENTER_SYSTEM);
					}
				}
			}
			break;
		case START_PROGRAM:
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)
				{
					if (!iap_load_app(FLASH_APP1_ADDR)) 
					{
						printf("APP固件不存在\r\n");
						cnt = 0;
						set_ymodem_status(WAIT_ENTER_SYSTEM);
					}
				}
			break;
		case UPDATE_PROGRAM:
			c_delay++;
			if(c_delay >= 100)
			{
				c_delay = 0;
				ymodem_c();
			}
			break;
		case UPDATE_SUCCESS:
			printf("/*****更新成功...******\r\n");
			cnt = 0;
			set_ymodem_status(START_PROGRAM);
			break;
		default:
			break;
	}
}


