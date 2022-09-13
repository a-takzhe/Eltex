#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)


#define YELLOW        do { printf("\033[0;33m");} while (0)
#define RED           do { printf("\033[0;31m");} while (0)
#define RESET         do { printf("\033[0m\n");} while (0) 
#define STAT_MS(prt)  do { YELLOW; prt; RESET;} while (0)
#define ERROR_MS(prt) do { RED; prt; RESET;} while (0)  

#define MAX_USERS      10
#define MAX_USER_NAME  64
#define MAX_MSG_SIZE   64
#define MAX_MSG        64
#define MAX_MQ_MSG     10


#define PAGE_SIZE      4096
#define FOR_READER     1
#define FOR_WRITER     2 

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// (3)priority - user deattach(for SERVER)
// (3)priority - get id and confirm connection form server (for CLIENT)
// (4)priority - user disconnected (for CLIENT)
// (5)priority - server stopped (for CLIENT)
// (2)priority - user attach
// (1)priority - user send message
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

             ///SEMAPHORES///

//***********Writer sembuf**********************//
// sembuf lock[3] = {{0,-2,0},{0,0,0},{0,1,0}}; //
// sembuf unlock[1] = {0,-1,0};                 //
//**********************************************//

//***********Reader sembuf**********************//
// sembuf lock[2] = {{0,0,0},{0,1,0}};          //
// sembuf unlock[1] = {0,1,0};                  //
//**********************************************//

struct PACK_T{
    char  message[MAX_MSG_SIZE];
    int   status;
    int   uid;
}
typedef package;

struct USER_T
{
    int   uid;
    int   active;
    char  name[MAX_USER_NAME];
    void* ptr;
    int   sem_id;
} 
typedef user;

#endif