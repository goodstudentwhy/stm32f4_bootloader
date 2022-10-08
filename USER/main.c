#include "sys.h"
#include "delay.h"
#include "signal_led.h"
#include "delay.h"
#include "IAP.h"
#include "schedule.h"


int main(void)
{ 
	boot_board_init();
	loop_check();
	while(1)
	{
		duty_loop();
	}
}


