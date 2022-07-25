#ifndef _COMMON_H_
#define _COMMON_H_

#include <string.h>
#include <math.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define handle_error(msg) \
        do { perror(msg); RESET; exit(EXIT_FAILURE); } while (0)

#define YELLOW        do { printf("\033[1;33m");} while (0)
#define RED           do { printf("\033[41m");} while (0)
#define RESET         do { printf("\033[0m");} while (0) 
#define STAT_MS(prt)  do { YELLOW; prt; RESET;} while (0)
#define ERROR_MS(prt) do { RED; prt; RESET;} while (0)  

#define P(i) (i+1)
#define MAX_USER 10
#define MAX_USER_NAME 32
#define MAX_MSG_SIZE 64
#define MAX_MSG 64

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// (2)priority - user attach
// (1)priority - user send message
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct PACK_T{
    char message[MAX_MSG_SIZE];
    int  q_id;
}
typedef package;

struct GUI_USER_T{
    int   q_id;
    char* name;
    int   active;
} 
typedef gui_user;
gui_user USERS[MAX_USER]; 


static int ID_LAST_MSG = -1;
char input_str[MAX_MSG_SIZE];
int X;

struct MESSAGE_LIST_T{
    char text[MAX_MSG_SIZE];
    int  u_id;
} typedef message_list;
message_list messages[MAX_MSG];

#endif