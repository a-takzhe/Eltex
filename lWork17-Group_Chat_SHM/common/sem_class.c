#include "sem_class.h"

//***********Writer sembuf***************************//
struct sembuf init[1] = {{0,2,0}};                   //
//***************************************************//

//***********Writer sembuf***************************//
struct sembuf wlock[3] = {{0,-2,0},{0,0,0},{0,1,0}}; //
struct sembuf wunlock[1] = {0,-1,0};                 //
//***************************************************//

//***********Reader sembuf**********************//
struct sembuf rlock[2] = {{0,0,0},{0,1,0}};     //
struct sembuf runlock[1] = {0,1,0};             //
//**********************************************//

char* compere_sem_file(const char* name, int cr)
{
    char* sem_file = (char*)calloc(128,sizeof(char));
    strcpy(sem_file, SEM_PATH);
    strcat(strcat(sem_file, name+1), ".sem");
    
    if(cr == 1)
    {
        if(open(sem_file, O_RDWR | O_CREAT, 777) == -1)
        {
            printf("Can't open file %s", sem_file);
            return NULL;
        }
    }
    return sem_file;
}

int create_sem(const char* name, int proj_id, int mode)
{
    char* nname = compere_sem_file(name, 1);
    if(mode == FOR_READER)
    {
        return create_reader_sem(nname, proj_id);
    }
    else if(mode == FOR_WRITER)
    {
        return create_writer_sem(nname, proj_id);
    }
    else
    {
        return -1;
    }
}

int create_reader_sem(char* name, int proj_id)
{
    key_t key;
    int sem_id;    

    key = ftok(name, proj_id);
    if(key == -1){
        handle_error("Can't get sem key!\n");
    }

    sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0777);
    if(sem_id == -1){
        handle_error("Can't get sem id!\n");
    }

    if(semop(sem_id, init, 1) == -1){
        handle_error("Can't first initialize sem!\n");
    }
    free(name);
    return sem_id;
}

int create_writer_sem(char* name, int proj_id)
{
    key_t key;
    int sem_id;
    
    key = ftok(name, proj_id);
    if(key == -1){
        printf("Can't get sem key for %s!\n", name);
        return -1;
    }

    sem_id = semget(key, 1, IPC_CREAT | 0777);
    if(sem_id == -1){
        printf("Can't get sem id for %s!\n", name);
        return -1;
    }
    free(name);
    return sem_id;
}

int sem_lock(int sem_id, int mode)
{
    // int ret;
    if(mode == FOR_READER)
    {
        return semop(sem_id, rlock, 2);
    }
    else if(mode == FOR_WRITER)
    {
        return semop(sem_id, wlock, 3);
    }
    else
    {
        return -1;
    }
    //return ret;
}

int sem_unlock(int sem_id, int mode)
{
    // int ret;
    if(mode == FOR_READER)
    {
        return semop(sem_id, runlock, 1);
    }
    else if(mode == FOR_WRITER)
    {
        return semop(sem_id, wunlock, 1);
    }
    else
    {
        return -1;
    }
    //return ret;
}

int sem_del(int sem_id, const char* name)
{
    if(semctl(sem_id, 0, IPC_RMID) != -1)
    {
        printf("Semaphore %s is deleted!\n", name);
    }
    if(strlen(name) > 0)
    {
        char* sem_file=compere_sem_file(name,0);

        if(remove(sem_file) != -1)
        {
            printf("file %s is deleted\n", sem_file);
        }
        free(sem_file);
    }
}

