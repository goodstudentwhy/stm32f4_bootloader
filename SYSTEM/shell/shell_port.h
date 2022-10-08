#ifndef __SHELL_PORT_H
#define __SHELL_PORT_H
#include "sys.h"
#include "shell.h"

extern Shell shell;

void user_shell_write(const char ch);
void user_shell_init(void);
void test_write(void);

#endif

