#include "commond.h"
#include "ymodem.h"
#include "shell_port.h"

boot_param_t boot_param = {star_jump_app};
#define SCB_AIRCR       (*(volatile unsigned long *)0xE000ED0C)  /* Reset control Address Register */
#define SCB_RESET_VALUE 0x05FA0004  

/*****YMODEM下载固件函数*******/
void ymodem_ota(void)
{
	boot_param.boot_sta = star_ymodem;
	set_ymodem_status(UPDATE_PROGRAM);
}
USER_SHELL_EXPORT_CMD(SHELL_TYPE_CMD_FUNC,ymodem_ota,ymodem_ota,ymodem_ota);

/*****重启函数*****/
void reboot(void)
{
	SCB_AIRCR = SCB_RESET_VALUE;
}
USER_SHELL_EXPORT_CMD(SHELL_TYPE_CMD_FUNC,reboot,reboot,reboot);

