#ifndef PARSER_H_
#define PARSER_H_

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(int argc, char** argv, char *projname, int* fork_num, char** newargw);
int bincheck(const char* __name__, char** token);

#endif