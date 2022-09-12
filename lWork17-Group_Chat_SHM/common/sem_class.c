#include "sem_class.h"

char* compere_sem_file(const char* name, int cr)
{
    char* sem_file = (char*)calloc(128,sizeof(char));
    strcpy(sem_file, SEM_PATH);
    strcat(strcat(sem_file, name+1), ".sem");
    
    if(cr == 1)
    {
        if(open(sem_file, O_RDWR | O_CREAT, 776) == -1)
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
        return NULL;
    }
}

int create_reader_sem(const char* name, int proj_id)
{
    key_t key;
    int sem_id;    

    key = ftok(name, proj_id);
    if(key == -1){
        handle_error("Can't get sem key!\n");
    }

    sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL);
    if(sem_id == -1){
        handle_error("Can't get sem id!\n");
    }
    free(name);
    return sem_id;
}

int create_writer_sem(const char* name, int proj_id)
{
    key_t key;
    int sem_id;
    
    key = ftok(name, proj_id);
    if(key == -1){
        printf("Can't get sem key for %s!\n", name);
        return -1;
    }

    sem_id = semget(key, 1, IPC_CREAT);
    if(sem_id == -1){
        printf("Can't get sem id for %s!\n", name);
        return -1;
    }
    free(name);
    return sem_id;
}

// int sem_lock(int sem_id)
// {
//     struct sembuf lock[2] = {{0,0,0},{0,1,0}};
//     int ret = semop(sem_id, rlock, 2);
//     return ret;
// }

// int sem_unlock(int sem_id)
// {
//     struct sembuf unlock[1] = {0,-1,0};
//     int ret = semop(sem_id, unlock, 1);
//     return ret;
// }

// int sem_lock_client(int uid)
// {
//     if(USERS[uid].active == -1){
//         printf("User with uid(%d) not exists!\n", uid);
//         return -1;
//     }
//     if(sem_lock(USERS[uid].sem_id) == -1){
//         printf("Server can't locked user sem (%s)!\n", USERS[uid].name);
//         return -1;
//     }
//     return 1;
// }

// int sem_unlock_client(int uid)
// {
//      if(USERS[uid].active == -1){
//         printf("User with uid(%d) not exists!\n", uid);
//         return -1;
//     }
//     if(sem_unlock(USERS[uid].sem_id) == -1){
//         printf("Server can't unlocked user sem (%s)!\n", USERS[uid].name);
//         return -1;
//     }
//     return 1;
// }

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


 