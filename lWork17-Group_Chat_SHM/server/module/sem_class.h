#ifndef SEM_CLASS_H
#define SEM_CLASS_H

#include "data.h"
    
//***********Writer sembuf**********************//
const struct sembuf wlock[3] = {{0,-2,0},{0,0,0},{0,1,0}}; //
const struct sembuf wunlock[1] = {0,-1,0};                 //
//**********************************************//

//***********Reader sembuf**********************//
struct sembuf rlock[2] = {{0,0,0},{0,1,0}};          //
struct sembuf runlock[1] = {0,1,0};                  //
//**********************************************//

int create_server_sem(const char* name);
int create_client_sem(const char* name);
int sem_lock(int sem_id);
int sem_unlock(int sem_id);
int sem_lock_client(int uid);
int sem_unlock_client(int uid);
int sem_del(int sem_id, const char* name);

#endif