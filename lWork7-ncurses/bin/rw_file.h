#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "compare.h"


u_short num_lines;
u_char isNote; 


int read_file(char *path, WINDOW* wnd);
int rewrite(WINDOW* wnd, int d);
int insert(char c);
int delete();
char get_symbol(int x, int y);
int end_ind(int y);
void clear_trow();