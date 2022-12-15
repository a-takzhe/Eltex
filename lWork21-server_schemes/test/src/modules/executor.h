#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include "parser.h"

int start_proc(char *path, int fork_num);

#endif