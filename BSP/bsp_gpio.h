#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "sys.h"
 

typedef struct 
{
	uint32_t RCC_GPIOx	:32;
	uint16_t gpio_pin	:16;
	uint16_t gpio_mode  :4;
	uint16_t gpio_otype :1;
	uint16_t gpio_speed	:4;
	uint16_t gpio_pupd	:2;
	
}gpio_config_t;

void gpio_out_in_init(GPIO_TypeDef* GPIOx,gpio_config_t gpio_config);
		 				    
#endif
