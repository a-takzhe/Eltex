#include "sem_class.h"

//***********Writer sembuf***************************//
struct sembuf wlock[3] = {{0,-2,0},{0,0,0},{0,1,0}}; //
struct sembuf wunlock[1] = {0,-1,0};                 //
//***************************************************//

//***********Reader sembuf**********************//
struct sembuf rlock[2] = {{0,0,0},{0,1,0}};     //
struct sembuf runlock[1] = {0,1,0};             //
//**********************************************//


// int create_server_sem(const char* name)
// {
//     key_t key;
//     int sem_id;
//     char sem_file[128] = SEM_PATH;

//     strcat(strcat(sem_file, name+1), ".sem");
//     open(sem_file, O_RDWR | O_CREAT, 776);

//     key = ftok(sem_file, PROJ_ID);
//     if(key == -1){
//         handle_error("Server Can't get sem key for server!\n");
//     }

//     sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL);
//     if(sem_id == -1){
//         handle_error("Server Can't get sem id for server!\n");
//     }
//     return sem_id;
// }

// int create_client_sem(const char* name)
// {
//     key_t key;
//     int sem_id;
    
//     key = ftok(name, PROJ_ID);
//     if(key == -1){
//         printf("Server Can't get sem key for client %s!\n", name);
//         return -1;
//     }

//     sem_id = semget(key, 1, IPC_CREAT);
//     if(sem_id == -1){
//         printf("Server Can't get sem key for client %s!\n", name);
//         return -1;
//     }
//     return sem_id;
// }

// int sem_lock(int sem_id)
// {
//     struct sembuf lock[2] = {{0,0,0},{0,1,0}};
//     int ret = semop(sem_id, rlock, 2);
//     return ret;
// }

// int sem_unlock(int sem_id)
// {
//     struct sembuf unlock[1] = {0,-1,0};
//     int ret = semop(sem_id, unlock, 1);
//     return ret;
// }

// int sem_lock_client(int uid)
// {
//     if(USERS[uid].active == -1){
//         printf("User with uid(%d) not exists!\n", uid);
//         return -1;
//     }
//     if(sem_lock(USERS[uid].sem_id) == -1){
//         printf("Server can't locked user sem (%s)!\n", USERS[uid].name);
//         return -1;
//     }
//     return 1;
// }

// int sem_unlock_client(int uid)
// {
//      if(USERS[uid].active == -1){
//         printf("User with uid(%d) not exists!\n", uid);
//         return -1;
//     }
//     if(sem_unlock(USERS[uid].sem_id) == -1){
//         printf("Server can't unlocked user sem (%s)!\n", USERS[uid].name);
//         return -1;
//     }
//     return 1;
// }

// int sem_del(int sem_id, const char* name)
// {
//     if(semctl(sem_id, 0, IPC_RMID) != -1)
//     {
//         printf("Server sem is deleted!\n");
//     }
//     if(strlen(name) > 0)
//     {
//         char sem_file[128] = SEM_PATH;
//         strcat(strcat(sem_file, name+1), ".sem");
//         if(remove(sem_file) != -1)
//         {
//             printf("file %s is deleted\n", sem_file);
//         }
//     }
// }


 