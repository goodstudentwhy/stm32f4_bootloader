#include "bsp_gpio.h" 
	   

void gpio_out_in_init(GPIO_TypeDef* GPIOx,gpio_config_t gpio_config)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(gpio_config.RCC_GPIOx, ENABLE);

	GPIO_InitStructure.GPIO_Pin = gpio_config.gpio_pin;
	GPIO_InitStructure.GPIO_Mode = gpio_config.gpio_mode;
	if(gpio_config.gpio_mode == GPIO_Mode_OUT)
		GPIO_InitStructure.GPIO_OType = gpio_config.gpio_otype;
	GPIO_InitStructure.GPIO_Speed = gpio_config.gpio_speed;
	GPIO_InitStructure.GPIO_PuPd = gpio_config.gpio_pupd;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}







