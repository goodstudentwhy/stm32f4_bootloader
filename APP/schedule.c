#include "schedule.h"
#include "timer.h"
#include "ymodem.h"
#include "signal_led.h"
#include "timer.h"
#include "serial.h"
#include "key.h"
#include "ymodem.h"
#include "shell_port.h"
#include "delay.h"
#include "IAP.h"
#include "commond.h"

int check_flag = 0;

signal_led_t *slgnal_led = NULL;


static void loop_1000hz(void)
{
	signal_handle(slgnal_led);
}

static void loop_500hz(void)
{
	
}

static void loop_100hz(void)
{
	static int app_cnt = 0;
	if(boot_param.boot_sta == star_ymodem)
		ymodem_task();
	else if(boot_param.boot_sta == star_jump_app)
	{
		app_cnt++;
		if(app_cnt == jump_app_time)
		{
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)
			{
				if (!iap_load_app(FLASH_APP1_ADDR)) 
				{
					printf("APP固件不存在\r\n");
				}
			}
		}
	}
	else;
}


static sched_task_t sched_task[]=
{
	{loop_1000hz,1000,0,0},
	{loop_500hz,500,0,0},
	{loop_100hz,100,0,0},
	
};

#define task_num (sizeof(sched_task)/sizeof(sched_task_t))
	
void loop_check(void)
{
	u8 index = 0;
	for(index = 0;index <task_num;index++ )
	{
		sched_task[index].interval_ticks = 1000/sched_task[index].rate_hz;
		if(sched_task[index].interval_ticks < 1)
		{
			sched_task[index].interval_ticks = 1;
		}
	}
	check_flag = 1;
}


void duty_loop(void)
{
	u8 index = 0;
	if(check_flag == 1)
	{
		for(index = 0;index < task_num;index++)
		{
			
			uint32_t tnow = get_sys_time_ms();
		
			if(tnow - sched_task[index].last_run >= sched_task[index].interval_ticks)
			{
				
				sched_task[index].last_run = tnow;
				
				sched_task[index].task_func();
			}	
		}
	}
}


void boot_board_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/****延时函数初始化****/
	delay_init(168);
	/****串口初始化****/
	serial_init();
	printf("串口初始化成功...\r\n");
	/****定时器初始化****/
	timer_init();
	printf("定时器初始化成功...\r\n");
	/****信号灯GPIO初始化****/
	signal_led_init();
	printf("信号灯GPIO初始化成功...\r\n");
	/******按键初始化*****/
	key_init();
	printf("按键初始化成功...\r\n");
	/****信号灯创建函数****/
	slgnal_led = signal_create(signal_led_on,signal_led_off);
	printf("\r\n");
	/****shell初始化****/
	user_shell_init();
	
	
}
