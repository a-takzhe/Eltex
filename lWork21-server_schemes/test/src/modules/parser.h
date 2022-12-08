#ifndef PARSER_H_
#define PARSER_H_

#include <unistd.h>
#include <string.h>

#define ALL_LA 22

int parse(int argc, char** argv, char *appName, int* fork_num, char** newargw);
//int check();

#endif