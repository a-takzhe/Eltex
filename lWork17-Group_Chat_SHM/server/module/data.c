#include "data.h"

void init_user_arr()
{
    for(int i = 0; i<MAX_USERS; i++)
    {
        USERS[i].active = -1;
    }
}

int can_add_user()
{
    for(int i = 0; i<MAX_USERS; i++)
    {
        if(USERS[i].active == -1)
        {
            return 1;
        }
    }
    return -1;
}

int add_user(const char* name, int sem_id, void* ptr)
{
    int ret = -1;
    for(int i = 0; i<MAX_USERS; i++)
    {
        if(USERS[i].active == -1)
        {
            USERS[i].active = 1;
            strncpy(USERS[i].name, name, MAX_USER_NAME);
            USERS[i].ptr = ptr;
            USERS[i].sem_id = sem_id;
        }
    }
    return ret;
}

void del_user(int uid)
{
    if(uid < 0 || uid >= MAX_USERS)
    {
        puts("bad uid!");
        return;
    }
    USERS[uid].active = -1;
}

