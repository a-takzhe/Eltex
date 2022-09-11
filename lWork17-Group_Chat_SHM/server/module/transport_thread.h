#ifndef TRANS_TH_H
#define TRANS_TH_H

#include "data.h"
#include "shm_class.h"
#include "sem_class.h"

void start_transport_thread(pthread_t* pth);
void cancel_transport_thread(pthread_t pth);
void* main_transport_func();

// int create_server_sem(const char* name);
// int create_client_sem(const char* name);
// int sem_lock(int sem_id);
// int sem_unlock(int sem_id);
// int sem_lock_client(int uid);
// int sem_unlock_client(int uid);
// int sem_del(int sem_id, const char* name);

#endif