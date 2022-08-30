#ifndef _DATA_CLI_H
#define _DATA_CLI_H

#include "../../../common.h"
#include <math.h>
#include <curses.h>
#include <termios.h>

#define P(i) (i+1)

char SERV_NAME[64];
char LOGIN[64];
mqd_t Q_USR_ID;
mqd_t Q_SERV_ID;
int   MY_UID;

user USERS[MAX_USER]; 


char INPUT_STR[MAX_MSG_SIZE];
int X;

struct MESSAGE_LIST_T{
    char text[MAX_MSG_SIZE];
    int  u_id;
}typedef message_list;

message_list MESSAGES[MAX_MSG];
int ID_LAST_MSG;

pthread_t pth_listener;
// pthread_t pth_;
// pthread_t pth_;

#endif