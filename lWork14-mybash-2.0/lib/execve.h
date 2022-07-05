#ifndef EXECVE_H_
#define EXECVE_H_

#include "strok.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h> 
#include <unistd.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)


#ifndef BUFSIZE
#define BUFSIZE 256  
#endif

char GLOB_BUFF[BUFSIZE];
int mystdout, mystdin;

int exec(char* str);
void initdesc();

#endif