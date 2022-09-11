#include "shm_class.h"

void *create_server_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IROTH);
    if(shm_fd == -1){
        handle_error("Can't open fd shared memmory for server!\n");
    }

    if(ftruncate(shm_fd, (off_t)PAGE_SIZE) == -1){
        handle_error("Can't trunc shmem for server!\n");
    }
    
    sh_ptr = mmap(0, sizeof(package), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(*((int*)sh_ptr) == -1){
        handle_error("Can't mmap shmem for server!\n");
    }
    write_to_shm("", 10, -1, sh_ptr);
    return sh_ptr;
}

void *attach_client_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;

    shm_fd = shm_open(name, O_WRONLY, S_IRWXU | S_IRWXG | S_IROTH);
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

int write_to_shm(const char* mes, int status, int uid, const void* ptr)
{
    package* pack = (package*)ptr;
    
    if(USERS[uid].active != 1 && uid != -1)
    {
        printf("User with uid(%d) not exists!\n", uid);
        return -1;
    }

    strncpy(pack->message, mes, MAX_MSG_SIZE);
    pack->status = status;
    pack->uid = uid;

    return 1;
}

package* read_from_shm(const void* ptr)
{
    package* new_pack = (package*)calloc(1, sizeof(package));
    package* pack = (package*)ptr;
    if(pack->status == -1){
        return NULL;
    }
    new_pack->status = pack->status;
    new_pack->uid = pack->uid;
    strncpy(new_pack->message, pack->message, MAX_MSG_SIZE);
    pack->status = -1;
    return new_pack;
}

void close_all_shm()
{
    for(int i = 0; i < MAX_USERS; i++)
    {
        if(USERS[i].active == 1){
            close_shm(i);
        }
    }
}

void close_shm(int uid)
{
    if(munmap(USERS[uid].ptr, sizeof(package))==-1)
    {
        printf("Server can't munmap from %s shm\n", USERS[uid].name);
    }
    else{
        printf("Server munmap from %s shm\n", USERS[uid].name);
    }
}

void delete_shm(const char* name)
{
    if(shm_unlink(name) == -1)
    {
        printf("Server cnt't unlink %s shm!\n", name);
    }

    else{
        printf("Server unlink %s shm!\n", name);
    }
}


