#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H
#include "sys.h"
#include "stdbool.h"

typedef struct
{
	uint32_t period 		:16; //�Զ���װ��ֵ
	uint16_t Prescaler		:16; //��ʱ����Ƶ
	uint16_t countermode	:8;  //������ʽ
	uint16_t clockdivision	:12; //ʱ�ӷָ�
	
	uint8_t irq_channel		:8;  //�ж�����
	uint8_t irq_preemption	:8;  //��ռ���ȼ�
	uint8_t irq_subpriority :8;  //�����ȼ�
	bool    enble_sta		:1;	 //�Ƿ�ʹ�ܶ�ʱ��
	
}timer_config_t;
void timer_base_level_init(uint32_t RCC_TIMx,TIM_TypeDef* TIMx,timer_config_t timer_config);


#endif

