#ifndef EXECVE_H_
#define EXECVE_H_

#include "strok.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include <unistd.h>


int exec(char* str);

#endif