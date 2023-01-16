#ifndef EXECUTOR_H_
#define EXECUTOR_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h> 
#include "parser.h"

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)


//int start_proc(char *path, int fork_num);
int task_manager(char *path, int fork_num);
static void *start_proc(void* arg);

#endif