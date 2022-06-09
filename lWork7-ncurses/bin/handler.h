#ifndef HANDLER_H__
#define HANDLER_H__

#include <math.h>
#include "memw.h"
#include "rw_file.h"
#include <stdio.h>

#define NEW_LINE 0012

int main_handler();
int menu_processing(int key, WINDOW **curw);
void to_note(WINDOW **curw, int fl);
void to_menu(WINDOW **curw);

void dec_x();
void inc_x();
void dec_y();
void inc_y();
int can_x(short v);
int can_y(short v);

void insert_symbol(int key, WINDOW* wnd);
void delete_symbol(WINDOW *wnd);
int new_line();
#endif