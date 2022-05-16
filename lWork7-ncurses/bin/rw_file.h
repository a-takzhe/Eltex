#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

char NOTE[255][255];
unsigned int lln;

int read_file(char *path, WINDOW* wnd);
int nwrite(WINDOW* wnd);
char* insert(WINDOW* wnd, WINDOW* wnd2, int x, int y, char c);
char* delete(int x, int y);