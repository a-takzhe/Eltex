#ifndef SHM_CLASS_H
#define SHM_CLASS_H

#include "common.h"

void *create_shm(const char* name, int mode);
void *create_reader_shm(const char* name);
void *create_writer_shm(const char* name);

int write_to_shm(const char* mes, int status, int uid, const void* ptr);
package* read_from_shm(const void* ptr);
void close_all_shm();
void close_shm(const void* ptr, const char* name);
void delete_shm(const char* name);

#endif