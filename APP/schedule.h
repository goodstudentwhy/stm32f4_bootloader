#ifndef __SCHEDULE_H
#define __SCHEDULE_H

#include "sys.h"

typedef struct
{
	void(*task_func)(void);
	uint16_t rate_hz;
	uint16_t interval_ticks;
	uint32_t last_run;
}sched_task_t;

void loop_check(void);

void duty_loop(void);
void boot_board_init(void);


#endif

