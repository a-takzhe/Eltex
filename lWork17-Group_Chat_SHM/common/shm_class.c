#include "shm_class.h"

void *create_shm(const char* name, int mode)
{
    if(mode == FOR_READER)
    {
        return create_reader_shm(name);
    }
    else if(mode == FOR_WRITER)
    {
        return create_writer_shm(name);
    }
    else
    {
        return NULL;
    }
}

void *create_reader_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;
    
    shm_fd = shm_open(name, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IROTH);
    if(shm_fd == -1){
        handle_error("Can't open fd shared memmory!\n");
    }

    if(ftruncate(shm_fd, (off_t)PAGE_SIZE) == -1){
        handle_error("Can't ftruncate shared memory!\n");
    }
    
    sh_ptr = mmap(0, sizeof(package), PROT_READ, MAP_SHARED, shm_fd, 0);
    if(*((int*)sh_ptr) == -1){
        handle_error("Can't mmap shared memmory!\n");
    }
    return sh_ptr;
}

void *create_writer_shm(const char* name)
{
    int shm_fd;
    void *sh_ptr;

    shm_fd = shm_open(name, O_RDWR, S_IRWXU | S_IRWXG | S_IROTH);
    if(shm_fd == -1){
        printf("Can't open fd shared memmory for %s!\n", name);
        return NULL;
    }
    
    sh_ptr = mmap(0, sizeof(package), PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(*((int*)sh_ptr) == -1){
        printf("Can't mmap shmem for %s!\n", name);
        return NULL;
    }
    return sh_ptr;
}


int write_to_shm(const char* mes, int status, int uid, const void* ptr)
{
    package* pack = (package*)ptr;
    
    // if(USERS[uid].active != 1 && uid != -1)
    // {
    //     printf("User with uid(%d) not exists!\n", uid);
    //     return -1;
    // }

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

// void close_all_shm()
// {
//     for(int i = 0; i < MAX_USERS; i++)
//     {
//         if(USERS[i].active == 1){
//             close_shm(i);
//         }
//     }
// }

void close_shm(const void* ptr, const char* name)
{
    if(munmap(ptr, sizeof(package))==-1)
    {
        printf("Can't munmap from %s shm\n",name);
    }
    else{
        printf("munmap from %s shm success\n",name);
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


