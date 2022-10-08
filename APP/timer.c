#include "timer.h"
#include "bsp_timer.h"
#include "config.h"
#include "signal_led.h"

timer_config_t timer3_config = TIME3_CONFIG;
timer_config_t timer5_config = TIME5_CONFIG;

void timer_init(void)
{
	timer_base_level_init(RCC_APB1Periph_TIM3,TIM3,timer3_config);
	timer_base_level_init(RCC_APB1Periph_TIM5,TIM5,timer5_config);
	TIM_Cmd(TIM5,DISABLE);
}


void  SysTick_Configuration(void)
{
	RCC_ClocksTypeDef  rcc_clocks;
	uint32_t         cnts;

	RCC_GetClocksFreq(&rcc_clocks);
	cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts / 8;
	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

u32 systime_ms = 0;
void sys_time(void)
{
	systime_ms++;
}

uint32_t get_sys_time_ms(void)
{
	return systime_ms;
}


