#ifndef _COMMON_H_
#define _COMMON_H_

#define P(i) (i+1)
#define MAX_USER 10
#define MAX_MSG_SIZE 64
#define MAX_MSG 64

struct GUI_USER_T{
    char* name;
    int active;
} typedef gui_user;
gui_user users[MAX_USER]; 


char input_str[MAX_MSG_SIZE];
int X;

struct MESSAGE_LIST_T{
    char* text;
    int u_id;
} typedef message_list;
message_list messages[MAX_MSG];
int ID_LAST_MSG;

#endif