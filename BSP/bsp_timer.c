#include "bsp_timer.h"
#include "stdio.h"
#include "timer.h"
#include "ymodem.h"

Buffer recvBuf;

void timer_base_level_init(uint32_t RCC_TIMx,TIM_TypeDef* TIMx,timer_config_t timer_config)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_TIMx,ENABLE);  
	
	TIM_TimeBaseInitStructure.TIM_Period = timer_config.period; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=timer_config.Prescaler;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=timer_config.countermode; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=timer_config.clockdivision; 
	
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE); 
	 
	
	NVIC_InitStructure.NVIC_IRQChannel=timer_config.irq_channel; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=timer_config.irq_preemption; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=timer_config.irq_subpriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIMx,timer_config.enble_sta);
}

/****定时器3中断函数******/
void TIM3_IRQHandler(void)
{
	static int led_sta = 0;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		sys_time();
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update); 
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
		TIM_Cmd(TIM5,DISABLE);
		ymodem_recv(&recvBuf);
	}
}
