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

typedef struct
{
	u8 boot_sta;
}boot_param_t;

extern boot_param_t boot_param;

#endif

