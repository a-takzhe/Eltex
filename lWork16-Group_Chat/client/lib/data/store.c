#include "store.h"

int add_msg(char* text, int uid)
{
    ID_LAST_MSG += 1;
    strncpy(MESSAGES[ID_LAST_MSG].text, text, MAX_MSG_SIZE);
    MESSAGES[ID_LAST_MSG].u_id = uid;

    if(ID_LAST_MSG == MAX_MSG-1){
        ID_LAST_MSG = 9;
        for (int i = 0; i < 10; i++)
        {
            strncpy(MESSAGES[i].text, MESSAGES[MAX_MSG-11+i].text, MAX_MSG_SIZE);
            MESSAGES[i].u_id = MESSAGES[MAX_MSG-11+i].u_id;
        }
    }
    return 1;
}

int add_usr(char* name, int uid)
{
    static int user_cnt = 0;
    if(user_cnt == MAX_USER-1) return 0;
    strncpy(USERS[user_cnt].name, name, MAX_USER_NAME);   
    
    USERS[user_cnt].active = 1;    
    USERS[user_cnt].uid = uid;
    USERS[user_cnt].q_id = 5;
    user_cnt++;
    return user_cnt;
}

void clear_input()
{
    for (int i = X; i >= 0; i--)
    {
        INPUT_STR[i] = 0;
    }
    X=0;
}


