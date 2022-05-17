#include "compare.h"
#include "rw_file.h"


int change_x(WINDOW *wnd, point *p, short v);
int change_y(point *p, short v);
int main_handler();
int menu_processing(int key, WINDOW **curw, point* p);