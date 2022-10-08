#include "signal_led.h"
#include "config.h"
#include "timer.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsp_uart.h"
#include "shell_port.h"

gpio_config_t red_signal_led_config = READ_LED_GPIO_CONFIG;

/****信号灯闪烁频率设置******/
int SIGNAL_TICK = 1000;
USER_SHELL_EXPORT_VAR(SHELL_TYPE_VAR_INT, SIGNAL_TICK, &SIGNAL_TICK, test);
/******************/

/*****信号灯GPIO初始化******/
void signal_led_init(void)
{
	gpio_out_in_init(GPIOF,red_signal_led_config);
}

/*****信号灯打开函数******/
void signal_led_on(void)
{
	GPIO_WriteBit(GPIOF,red_signal_led_config.gpio_pin,LED_ON);
}

/*****信号灯关闭函数******/
void signal_led_off(void)
{
	GPIO_WriteBit(GPIOF,red_signal_led_config.gpio_pin,LED_OFF);
}

/**
 *名称：signal_led_toggle_state
 *功能：信号灯开启或关闭函数
 *输入：
 * @select: 0：打开信号灯
			1：关闭信号灯
**/
void signal_led_select(BitAction select)
{
	GPIO_WriteBit(GPIOF,red_signal_led_config.gpio_pin,select);
}

/**
 * 名称: signal_led_toggle_state
 * 功能：信号灯状态转换函数
 * 输入: 
 * @signal_handle: 信号灯句柄
**/
void signal_led_toggle_state(signal_led_t *signal_handle)
{
	if(signal_handle->signal_led_start == SIGNAL_STAR)
	{
		if(signal_handle->signal_led_state == LED_OFF)
		{
			signal_handle->on_sta();
			signal_handle->signal_led_state = LED_ON;
		}else if(signal_handle->signal_led_state == LED_ON)
		{
			signal_handle->off_sta();
			signal_handle->signal_led_state = LED_OFF;
		}
	}
}


/**
 * 名称: signal_handle
 * 功能：信号灯处理函数
 * 输入: 
 * @ctl_handle: 信号灯句柄
**/
void signal_handle(signal_led_t *ctl_handle)
{
	static int current_time = 0;
	if(current_time != get_sys_time_ms())
	{
		current_time = get_sys_time_ms();
		if((current_time%SIGNAL_TICK) == 0)
		{
			signal_led_toggle_state(ctl_handle);
		}
	}
}

/**
 * 名称: signal_create
 * 功能：信号灯功能创建
 * 输入: 
 * @on_sta: 信号灯开启函数
 * @off_sta: 信号灯关闭函数
 * 返回：
 * @signal_led_t：信号灯句柄
**/
signal_led_t *signal_create(void (*on_sta)(void),void (*off_sta)(void))
{
	signal_led_t *signal_led = NULL;
	
	signal_led = (signal_led_t *)malloc(sizeof(signal_led_t));
	memset(signal_led,0,sizeof(signal_led_t));
	
	off_sta();
	
	signal_led->on_sta = on_sta;
	signal_led->off_sta = off_sta;
	signal_led->signal_led_state = LED_OFF;
	signal_led->signal_led_start = SIGNAL_STAR;
	return signal_led;
}

