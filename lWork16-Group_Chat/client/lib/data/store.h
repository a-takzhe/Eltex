#ifndef _STORE_H_
#define _STORE_H_

#include "data.h"

int add_msg(char* text, int uid);
int add_usr(char* name, int uid);
void user_disconnect(int uid);
void clear_input();

#endif