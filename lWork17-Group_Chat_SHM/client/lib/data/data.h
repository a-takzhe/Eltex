#ifndef _DATA_CLI_H
#define _DATA_CLI_H

#include "../../../common/sem_class.h"
#include "../../../common/shm_class.h"
#include <math.h>
#include <curses.h>
#include <termios.h>

#define P(i) (i+1)

int   PROJ_ID;
int   SERVER_SEM;
int   MY_SEM;
void* SERVER_PTR;
void* MY_PTR;


int  MY_UID;
char SERV_NAME[64];
char LOGIN[MAX_USER_NAME];
user USERS[MAX_USERS]; 

struct MESSAGE_LIST_T
{
    char text[MAX_MSG_SIZE];
    char name[MAX_USER_NAME];
    int  u_id;
}typedef message_list;

message_list MESSAGES[MAX_MSG];
int ID_LAST_MSG;

char INPUT_STR[MAX_MSG_SIZE];
int  X;

pthread_t pth_listener;

#endif