#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H
#include "sys.h"
#include "stdbool.h"

typedef struct
{
	uint32_t period 		:16; //自动重装载值
	uint16_t Prescaler		:16; //定时器分频
	uint16_t countermode	:8;  //计数方式
	uint16_t clockdivision	:12; //时钟分割
	
	uint8_t irq_channel		:8;  //中断类型
	uint8_t irq_preemption	:8;  //抢占优先级
	uint8_t irq_subpriority :8;  //子优先级
	bool    enble_sta		:1;	 //是否使能定时器
	
}timer_config_t;
void timer_base_level_init(uint32_t RCC_TIMx,TIM_TypeDef* TIMx,timer_config_t timer_config);


#endif

