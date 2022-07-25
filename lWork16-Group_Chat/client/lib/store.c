#include "store.h"

int add_msg(char* text, int u_id)
{
    ID_LAST_MSG += 1;
    strncpy(messages[ID_LAST_MSG].text, text, MAX_MSG_SIZE);
    messages[ID_LAST_MSG].u_id = u_id;

    if(ID_LAST_MSG == MAX_MSG-1){
        ID_LAST_MSG = 9;
        for (int i = 0; i < 10; i++)
        {
            strncpy(messages[i].text, messages[MAX_MSG-11+i].text, MAX_MSG_SIZE);
            messages[i].u_id = messages[MAX_MSG-11+i].u_id;
        }
    }
}

int add_usr(char* name, int u_id)
{
    static int user_cnt = 0;

    if(user_cnt == MAX_USER-1) return 0;

    if(u_id != -1){
        free(USERS[u_id].name);
        USERS[u_id].name = NULL;
        USERS[u_id].active = 0;
    }

    USERS[user_cnt].name = (char*)malloc(MAX_USER_NAME);
    strncpy(USERS[user_cnt].name, name, MAX_USER_NAME);   
    USERS[user_cnt].active = 10;    
    user_cnt++;
    return 1;
}



