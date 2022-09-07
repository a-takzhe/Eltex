#ifndef SEM_CLASS_H
#define SEM_CLASS_H

#include "data.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h> 
#include <fcntl.h>        

int create_server_sem(const char* name);
int create_client_sem(const char* name);
int sem_lock(int sem_id);
int sem_unlock(int sem_id);
int sem_lock_client(int uid);
int sem_unlock_client(int uid);
int sem_del(int sem_id);

#endif