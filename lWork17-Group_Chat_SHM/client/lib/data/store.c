#include "store.h"

int add_msg(char* text, int uid)
{
    ID_LAST_MSG += 1;
    strncpy(MESSAGES[ID_LAST_MSG].text, text, MAX_MSG_SIZE);
    
    int i;
    for (i = 0; i < MAX_USERS; i++)
    {
        if(USERS[i].uid == uid){
            break;
        }
    }
    strncpy(MESSAGES[ID_LAST_MSG].name, USERS[i].name, MAX_USER_NAME);
    MESSAGES[ID_LAST_MSG].u_id = uid;

    if(ID_LAST_MSG == MAX_MSG-1){
        ID_LAST_MSG = 9;
        for (int i = 0; i < 10; i++)
        {
            strncpy(MESSAGES[i].text, MESSAGES[MAX_MSG-11+i].text, MAX_MSG_SIZE);
            strncpy(MESSAGES[i].name, MESSAGES[MAX_MSG-11+i].name, MAX_USER_NAME);
            // MESSAGES[i].u_id = MESSAGES[MAX_MSG-11+i].u_id;
        }
    }
    return 1;
}

void init_user_arr()
{
    for(int i = 0; i<MAX_USERS; i++)
    {
        USERS[i].active = -1;
    }
}

int add_usr(char* name, int uid)
{
    for (int i = 0; i < MAX_USERS; i++)
    {
        if(USERS[i].active == -1)
        {
            USERS[i].active = 1;    
            USERS[i].uid = uid;
            strncpy(USERS[i].name, name, MAX_USER_NAME);
            return i;   
        }
    }
    return -1;
}

void user_disconnect(int uid)
{
    for (size_t i = 0; i < MAX_USERS; i++)
    {
        if(USERS[i].uid == uid)
        {
            USERS[i].active = -1;    
            USERS[i].uid = -1;
        }
    }
}

void clear_input()
{
    for (int i = X; i >= 0; i--)
    {
        INPUT_STR[i] = 0;
    }
    X=0;
}


