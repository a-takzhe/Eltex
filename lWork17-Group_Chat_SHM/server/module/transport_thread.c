#include "transport_thread.h"


void start_transport_thread(pthread_t* pth)
{
    int err = pthread_create(pth, NULL, main_transport_func, NULL);
    if (err != 0){
        handle_error_en(err, "pthread_create");
    }
    STAT_MS(printf("Transport thread started!"));
}

void cancel_transport_thread(pthread_t pth)
{
    int err = pthread_cancel(pth);
    if(err != 0){
        handle_error_en(err, "pthread_cancel");   
    }
    ERROR_MS(printf("Transport thread stopped!"));
}

int read_msg(package** pack)
{
    if(sem_lock(SEM_ID, FOR_READER) == -1)
    {
        puts("Error! Server can`t lock semaphore!\nListener STOPPED!");
        return -1;
    }
    if((*pack = read_from_shm(SHM_PTR)) == NULL)
    {
        puts("Trubble with read file!");
        return -1;
    }
    if(sem_unlock(SEM_ID, FOR_READER) == -1)
    {
        puts("Error! Server can`t unlock semaphore!\nListener STOPPED!");
        return -1;
    }
    return 1;
}

void* main_transport_func()
{
    package* pack;

    while (1)
    {
        read_msg(&pack);
        
        if(pack != NULL)
        {
            if(pack->status == 1)
            {
                printf("Client (%s) send msg (%s)\n", USERS[pack->uid].name, pack->message);
                send_to_other_clients(pack->uid, pack->message, 1);
            }
            else if(pack->status == 2)
            {
                STAT_MS(printf("Attach user (%s)!", pack->message));
                client_attach(*pack);
                STAT_MS(printf("User(%s) attached!", pack->message));
            }
            else if(pack->status == 3)
            {
                STAT_MS(printf("User (%s) deattach!", pack->message));
                client_deattach(*pack);
                STAT_MS(printf("User (%s) deattached!", pack->message));
            }
            else{ERROR_MS(puts("Unrecognize message!!"));}
            free(pack);
        }
    }
    return NULL;
}