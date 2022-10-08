#include "key.h"
#include "config.h"
#include "delay.h"

gpio_config_t key_config = KEY_CONFIG;

/**
 *名称：key_init
 *功能：按键gpio初始化
**/
void key_init(void)
{
	gpio_out_in_init(GPIOE,key_config);
}

/**
 *名称：key_scan
 *功能：按键扫描
 *输出
 @return 0：无按键触发
		 1：按键key0触发
		 2：按键key1触发
		 3：按键key2触发
**/
u8 key_scan(void)
{
	if(KEY0==0||KEY1==0||KEY2==0)
	{
		delay_ms(10);
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
	}
	return 0;
}