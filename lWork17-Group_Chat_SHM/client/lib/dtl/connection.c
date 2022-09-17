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

void attach_to_server_ipc(const char* name)
{
    STAT_MS(printf("Connection to server (%s)...",name));
    if((SERVER_PTR = create_shm(name, FOR_WRITER)) == NULL)
    {
        handle_error("Can't connect to server shm");
    }
    puts("Shm connected!");
    if((SERVER_SEM = create_sem(name, PROJ_ID, FOR_WRITER))==-1)
    {
        handle_error("Can't connect to server sem");
    }
    puts("Semaphore is attached!");
    sleep(1);
}

int attach_to_server()
{
    int ret = 1;
    package* pack = NULL;
    
    write_message(LOGIN, 2);
    ret = read_message(&pack);
    if(pack->status == 3 && !strcmp(pack->message, "Attach successe!"))
    {
        MY_UID = pack->uid;
    }
    else { ret = -1; }

    if(pack != NULL) free(pack);
    return ret;
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
                close_server_ipc();
                delete_my_ipc();
                wend();
                puts("Server stopped");
                exit(EXIT_FAILURE);
                return NULL;
            }
            else{ERROR_MS(puts("Unrecognize message!!"));}
            free(pack);
        }
    } 
}
