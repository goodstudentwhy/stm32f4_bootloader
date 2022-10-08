#ifndef __SIGNAL_LED_H
#define __SIGNAL_LED_H

#include "sys.h"
#include "bsp_gpio.h" 

#define	LED_ON  Bit_RESET
#define	LED_OFF  Bit_SET

#define SIGNAL_STOP 0
#define SIGNAL_STAR 1


typedef struct
{
	u8 signal_select_led;
	u8 signal_led_state;
	u8 signal_led_start;
	void (*on_sta)(void);
	void (*off_sta)(void);
}signal_led_t;

void signal_led_init(void);
void signal_led_on(void);
void signal_led_off(void);
void signal_handle(signal_led_t *ctl_handle);
void signal_led_select(BitAction select);
void signal_led_toggle_state(signal_led_t *signal_handle);
signal_led_t *signal_create(void (*on_sta)(void),void (*off_sta)(void));

#endif

