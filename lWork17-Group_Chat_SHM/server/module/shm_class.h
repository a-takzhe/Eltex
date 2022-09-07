#ifndef SHM_CLASS_H
#define SHM_CLASS_H

#include "data.h"
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h>        

void *create_server_shm(const char* name);
void *attach_client_shm(const char* name);
int write_to_shm(const char* mes, int status, int uid, const void* ptr);
package* read_from_shm(const void* ptr);
void close_all_shm();
void close_shm(int uid);
void delete_shm(const char* name);

#endif