#include "serial.h"
#include "bsp_gpio.h" 

uart_config_t uart1_config = UART1_CONFIG;
gpio_config_t uart1_gpio_config = UART1_GPIO_CONFIG;

/******串口初始化函数******/
void serial_init(void)
{
	uart_init(GPIOA,USART1,uart1_config,uart1_gpio_config);
}