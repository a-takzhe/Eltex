#ifndef STROK_H_
#define STROK_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int isExit(char* str);
int uEscape(char* str);
int fillargv(char** argv, char* str);
int get_nparam(char* str);
int get_nfunc(char* str);


#endif