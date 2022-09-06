#ifndef SHM_CLASS_H
#define SHM_CLASS_H

#include "data.h"
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>        

void *create_server_shm(const char* name);
void *attach_client_shm(const char* name);
int write_to_shm(const char* mes, int prioryty, const void* ptr);
int close_all_ahm();
int close_shm();
int delete_shm();

#endif