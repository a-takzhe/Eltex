// #include "compare.h"
#include "rw_file.h"
#include <math.h>


int change_x(point p, short v);
void dec_x();
void inc_x();
void dec_y();
void inc_y();
int change_y(point p, short v);
int can_x(short v);

int main_handler();
int menu_processing(int key, WINDOW **curw);
int back_click(WINDOW *wnd);
void menu_back(WINDOW **curw);
void to_menu(WINDOW **curw);