#ifndef __COMMOND_H
#define __COMMOND_H
#include "sys.h"

#define jump_app_time 500

enum
{
	star_jump_app = 0,
	star_ymodem,
	hold_boot,
};

enum
{
	none_error = 0,
	app_addr_error = -1,
	erase_sector_error = -2,
	write_flash_error = -3,
};

typedef struct
{
	u8 boot_sta;
	int32_t error_code;
}boot_param_t;

extern boot_param_t boot_param;

#endif

