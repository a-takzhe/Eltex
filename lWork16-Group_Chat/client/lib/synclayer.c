#include "synclayer.h"

void mutex_init()
{
    pthread_mutex_init(&usr_mutex, NULL);
    pthread_mutex_init(&msg_mutex, NULL);
    // usr_mutex = PTHREAD_MUTEX_INITIALIZER;
    // msg_mutex = PTHREAD_MUTEX_INITIALIZER;
}

int sync_add_usr(char* name, int uid)
{    
    int err, i;
    if((err = pthread_mutex_lock(&usr_mutex)) == 0)
    {
        i = add_usr(name, uid);
        update_usr_area();
        
        err = pthread_mutex_unlock(&usr_mutex);
        if(err != 0) handle_error_en(err, "pthread_mutex_unlock");        
        return i;
    }
    return i;
}


int sync_add_msg(char* text, int uid)
{
    int err, i;
    if((err = pthread_mutex_lock(&msg_mutex)) == 0)
    {
        i = add_msg(text, uid);
        update_msg_area();
        
        err = pthread_mutex_unlock(&msg_mutex);
        if(err != 0) handle_error_en(err, "pthread_mutex_unlock");        
        return i;
    }
    return i;
}

