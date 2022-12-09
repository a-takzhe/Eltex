#ifndef PARSER_H_
#define PARSER_H_

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse(int argc, char** argv, char *appName, int* fork_num, char** newargw);

#endif