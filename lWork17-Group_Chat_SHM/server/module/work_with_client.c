#include "work_with_client.h"

int send_message(int uid_to, int uid_from, const char* mes, int status)
{
    if(sem_lock(USERS[uid_to].sem_id, FOR_WRITER) == -1){
        printf("Error! Server can`t lock semaphore for %s!\n", USERS[uid_to].name);
        return -1;
    }

    write_to_shm(mes, status, uid_from, USERS[uid_to].ptr);

    if(sem_unlock(USERS[uid_to].sem_id, FOR_WRITER) == -1){
        printf("Error! Server can`t unlock semaphore for %s!\n", USERS[uid_to].name);
        return -1;
    }
    return 1;
}

int send_to_other_clients(int uid, const char* mes, int status)
{
    for (size_t i = 0; i < MAX_USERS; i++)
    {
        if(i != uid && USERS[i].active != -1)
        {
            printf("Send from (%s) to (%s) mes(%s)\n", USERS[uid].name, USERS[i].name, mes);
            send_message(i, uid, mes, status);
        }
    }
    return 1;    
}

int send_old_to_new_clients(int uid, const char* mes, int status)
{
    for (size_t i = 0; i < MAX_USERS; i++)
    {
        if(i != uid && USERS[i].active != -1)
        {
            printf("Send to (%s), about old user(%s)\n", mes, USERS[i].name);
            send_message(uid, i, USERS[i].name, status);
        }
    }
    return 1;    
}

int client_attach(package pack)
{
    void* ptr;
    int sem_id;
    int uid = -1;

    if((ptr = create_shm(pack.message, FOR_WRITER)) == NULL){
        printf("Can't create shm for client %s\n", pack.message);
        return -1;
    }
    printf("Created shm for (%s)\n", pack.message);

    if((sem_id = create_sem(pack.message, PROJ_ID, FOR_WRITER)) == -1){
        printf("Can't create sem for client %s\n", pack.message);
        close_shm(ptr, pack.message);
        return -1;
    }
    printf("Created sem for (%s)\n", pack.message);

    if(can_add_user() == -1)
    {
        printf("User list is full. Can't add new user %s\n!", pack.message);
        send_message(uid, uid, "Attach failure!", 3);
        close_shm(ptr, pack.message);
        return -1;
    }

    uid = add_user(pack.message, sem_id, ptr);
    send_message(uid, uid, "Attach successe!", 3);
    send_to_other_clients(uid, pack.message, 2);
    send_old_to_new_clients(uid, pack.message, 2);

    return 1;
}

int client_deattach(package pack)
{
    close_shm(USERS[pack.uid].ptr, USERS[pack.uid].name);
    send_to_other_clients(pack.uid, "deattach", 4);
    del_user(pack.uid);
    return 1;
}

int all_client_deattach()
{
    for (size_t i = 0; i < MAX_USERS; i++)
    {
        if(USERS[i].active != -1){
            send_message(i, i, "Server stopped", 5);
            close_shm(USERS[i].ptr, USERS[i].name);
        }
    }
    return 1;
}