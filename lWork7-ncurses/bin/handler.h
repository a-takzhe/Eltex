#ifndef HANDLER_H__
#define HANDLER_H__

#include <math.h>
#include "memw.h"
#include "rw_file.h"
#include <stdio.h>

void dec_x();
void inc_x();
void dec_y();
void inc_y();
int can_x(short v);
int can_y(short v);

void insert_symbol(int key, WINDOW* wnd);
int new_line();
int main_handler();
int menu_processing(int key, WINDOW **curw);
int back_click(WINDOW *wnd);
void menu_back(WINDOW **curw);
void to_menu(WINDOW **curw);
#endif