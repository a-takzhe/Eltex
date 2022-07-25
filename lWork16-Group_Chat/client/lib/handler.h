#ifndef _HANDLER_H_
#define _HANDLER_H_

#include "gui.h"
#include "store.h"

#define KEY_ENTR 0012


int h_main();
void inc_x();
void dec_x();
int can_x(int v);
void delete_symbol(WINDOW *wnd);


#endif