#include "connection.h"

void create_my_ipc(const char* name)
{
    STAT_MS(printf("Statrt init ipc components (%s)...",name));

    MY_PTR = create_shm(name, FOR_READER);
    puts("Shm created!");

    PROJ_ID = get_proj_id();
    MY_SEM = create_sem(name, PROJ_ID, FOR_READER);
    puts("Semophore is created");
    
    sleep(1);
}

int attach_to_server(const char* name)
{
    package* pack;
    
    STAT_MS(printf("Connection to server (%s)...",name));
    if((SERVER_PTR = create_shm(name, FOR_WRITER)) == NULL)
    {
        ERROR_MS(printf("Can't connect to server shm"));
        return -1;
    }
    puts("Shm connected!");
    if((SERVER_SEM = create_sem(name, PROJ_ID, FOR_WRITER))==-1)
    {
        ERROR_MS(printf("Can't connect to server sem"));
        return -1;
    }
    puts("Semophore is attached!");

    write_message(LOGIN, 2);
    if(read_message(&pack) == -1)
    {
        return -1;
    }

    if(pack->status == 3 && !strcmp(pack->message, "Attach successe!"))
    {
        MY_UID = pack->uid;
    }
    else
    {
        free(pack);
        return -1;
    }
    free(pack);
    return 1;
}

void close_server_ipc()
{
    close_shm(SERVER_PTR, "server"); 
}

void delete_my_ipc()
{
    delete_shm(LOGIN);
    sem_del(MY_SEM, LOGIN);
}

void* listen_server()
{
    package* pack;
    while(1)
    {
        if(read_message(&pack) != -1)
        {
            if(pack->status == 1)
            {
                sync_add_msg(pack->message, pack->uid);
            }
            else if(pack->status == 2)
            {
                sync_add_usr(pack->message, pack->uid);
            }
            else if(pack->status == 4)
            {
                sync_user_disconnect(pack->uid);
            }
            else if(pack->status == 5)
            {
                free(pack);
                close_server_ipc();
                delete_my_ipc();
                return NULL;
            }
            else{ERROR_MS(puts("Unrecognize message!!"));}
            free(pack);
        }
    } 
}
