#include "communication.h"

int read_message(package** pack)
{
    //puts("start read from server");
    if(sem_lock(MY_SEM, FOR_READER) == -1){
        puts("Error! Can`t lock semaphore!\nListener STOPPED!");
        return -1;
    }

    if((*pack = read_from_shm(MY_PTR)) == NULL)
    {
        puts("No message");
        return -1;
    }

    if(sem_unlock(MY_SEM, FOR_READER) == -1){
        puts("Error! Can`t unlock semaphore!\nListener STOPPED!");
        return -1;
    }
    //printf("finish read from server (mes: %s)\n", (*pack)->message);
    return 1;
}

int write_message(const char* mes, int status)
{
    //puts("start write to server");
    if(sem_lock(SERVER_SEM, FOR_WRITER) == -1){
        printf("Error! Can`t lock server semaphore!\n");
        return -1;
    }

    write_to_shm(mes, status, MY_UID, SERVER_PTR);

    if(sem_unlock(SERVER_SEM, FOR_WRITER) == -1){
        printf("Error! Can`t unlock server semaphore!\n");
        return -1;
    }
    //puts("finish write to server");
    return 1;
}
