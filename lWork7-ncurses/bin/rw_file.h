#ifndef RWFILE_H__
#define RWFILE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memw.h"

char F_NAME[MAXCOL2];

int read_file(char *path);
int wFile();
void write_fname(WINDOW* wnd);
#endif