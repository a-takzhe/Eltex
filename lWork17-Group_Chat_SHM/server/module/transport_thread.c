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

void* main_transport_func()
{
    int i = 0;
    while (1)
    {
        if(sem_lock(SEM_ID, FOR_READER) == -1){
            puts("Error! Server can`t lock semaphore!\nListener STOPPED!");
            return NULL;
        }

        package* pack = read_from_shm(SHM_PTR);

        if(sem_unlock(SEM_ID, FOR_READER) == -1){
            puts("Error! Server can`t unlock semaphore!\nListener STOPPED!");
            return NULL;
        }
        
        if(pack != NULL)
        {
            if(pack->status == 1){
                send_to_other_clients(pack->uid, pack->message, 1);
            }
            else if(pack->status == 2)
            {
                STAT_MS(printf("Attach user (%s)", pack->message));
                client_attach(*pack);
                STAT_MS(printf("User(%s) attached!", pack->message));
            }
            else if(pack->status == 3){
                client_deattach(*pack);
            }
            else{ERROR_MS(puts("Unrecognize message!!"));}
            free(pack);
        }
    }
    return NULL;
}