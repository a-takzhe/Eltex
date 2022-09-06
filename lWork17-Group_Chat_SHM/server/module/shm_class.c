#include "shm_class.h"

void *create_server_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;

    shm_fd = shm_open(name, O_CREAT | O_RDONLY, S_IRWXU | S_IRWXG | S_IROTH);
    if(shm_fd == -1){
        handle_error("Can't open fd shared memmory for server!\n");
    }
    if(ftruncate(shm_fd, PAGE_SIZE) == -1){
        handle_error("Can't trunc shmem for server!\n");
    }
    
    sh_ptr = mmap(0, sizeof(package), PROT_READ, MAP_SHARED, shm_fd, 0);
    if(*((int*)sh_ptr) == -1){
        handle_error("Can't mmap shmem for server!\n");
    }
    return sh_ptr;
}

void *attach_client_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;

    shm_fd = shm_open(name,  O_WRONLY, S_IRWXU | S_IRWXG | S_IROTH);
    if(shm_fd == -1){
        printf("Can't open fd shared memmory for client %s!\n", name);
        return NULL;
    }
    
    sh_ptr = mmap(0, sizeof(package), PROT_READ, MAP_SHARED, shm_fd, 0);
    if(*((int*)sh_ptr) == -1){
        printf("Can't mmap shmem for client %s!\n", name);
        return NULL;
    }
    return sh_ptr;
}

int write_to_shm(const char* mes, int prioryty, const void* ptr)
{

}