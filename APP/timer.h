#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

void timer_init(void);
u16 Get_Time(u8,u16,u16);
void SysTick_Configuration(void);
uint32_t get_sys_time_ms(void);
u32 SysTick_GetTick(void);
void sys_time(void);
#endif
