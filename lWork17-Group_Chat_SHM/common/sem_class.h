#ifndef SEM_CLASS_H
#define SEM_CLASS_H

#include "common.h"

#define SEM_PATH  "./semaphores/sem-"

// //***********Writer sembuf***************************//
// const struct sembuf wlock[3] = {{0,-2,0},{0,0,0},{0,1,0}}; //
// const struct sembuf wunlock[1] = {0,-1,0};                 //
// //***************************************************//

// //***********Reader sembuf**********************//
// const struct sembuf rlock[2] = {{0,0,0},{0,1,0}};     //
// const struct sembuf runlock[1] = {0,1,0};             //
// //**********************************************//

char* compere_sem_file(const char* name, int cr);
int create_sem(const char* name, int proj_id, int mode);
int create_reader_sem(const char* name, int proj_id);
int create_writer_sem(const char* name, int proj_id);

int sem_lock(int sem_id);
int sem_unlock(int sem_id);
int sem_lock_client(int uid);
int sem_unlock_client(int uid);
int sem_del(int sem_id, const char* name);

#endif