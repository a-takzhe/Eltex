#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#define HTOOL_MES "[Insert File Name]: "
#define MAXCOL 256
#define MAXCOL2 64
#define MAXROW 128

char NOTE[MAXROW][MAXCOL];
char TROW[MAXCOL2];
u_short LLN;
u_char isNote; 


int read_file(char *path, WINDOW* wnd);
int nwrite(WINDOW* wnd);
char* insert(int x, int y, char c);
char* delete(int x, int y);
char get_symbol(int x, int y);
int end_ind(int y);
void clear_trow();