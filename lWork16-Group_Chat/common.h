#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>

#define handle_error(msg) \
        do { perror(msg); RESET; exit(EXIT_FAILURE); } while (0)

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


#define YELLOW        do { printf("\033[1;33m");} while (0)
#define RED           do { printf("\033[41m");} while (0)
#define RESET         do { printf("\033[0m");} while (0) 
#define STAT_MS(prt)  do { YELLOW; prt; RESET;} while (0)
#define ERROR_MS(prt) do { RED; prt; RESET;} while (0)  

#define MAX_USER 10
#define MAX_USER_NAME 32
#define MAX_MSG_SIZE 64
#define MAX_MSG 64

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// (3)priority - user deattach
// (2)priority - user attach
// (1)priority - user send message
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct PACK_T{
    char  message[MAX_MSG_SIZE];
    mqd_t u_id;
}
typedef package;

struct USER_T
{
    mqd_t q_id;
    int   uid;
    char name[MAX_USER_NAME];
    int   active;
} 
typedef user;

#endif