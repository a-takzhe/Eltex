#ifndef SEM_CLASS_H
#define SEM_CLASS_H

#include "common.h"

#define SEM_PATH  "./semaphores/sem-"

int get_proj_id();

char* compere_sem_file(const char* name, int cr);
int create_sem(const char* name, int proj_id, int mode);
int create_reader_sem(char* name, int proj_id);
int create_writer_sem(char* name, int proj_id);

int sem_lock(int sem_id, int mode);
int sem_unlock(int sem_id, int mode);
int sem_lock_client(int uid);
int sem_unlock_client(int uid);
int sem_del(int sem_id, const char* name);

#endif