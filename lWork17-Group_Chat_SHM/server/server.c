#include "module/transport_thread.h"

int isExit(char* str)
{
    return (strcmp(str, "exit") == 0 || strstr(str, "exit") != NULL);
}

int main(int argc, char* argv[])
{
    int opt, err;
    char* str = NULL;
    size_t len;
    ssize_t s_len;
    pthread_t pth_transport;
    
    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
            case 'n':
                strncpy(SERVER_NAME+1, optarg, 63);
                break;
            default:
                printf("unknown key %c!\n", opt);
                exit(EXIT_FAILURE);
                break;
        }
    }
    if(SERVER_NAME[1] == 0){
        puts("please, use option '-n' for set server name");
        exit(EXIT_FAILURE);
    }
    SERVER_NAME[0] = '/';

    //initialization message queue 
    STAT_MS(printf("Statrt init Server (%s)...",SERVER_NAME));
    SHM_PTR = create_shm(SERVER_NAME, FOR_READER);
    STAT_MS(printf("Server shm created!\nCreate server semophore..."));
    SEM_ID = create_sem(SERVER_NAME, PROJ_ID, FOR_READER);
    STAT_MS(printf("Server semophore is created"));


    //thread for communication between users  
    start_transport_thread(&pth_transport);
    

    //main thread for correct finalization server 
    while (1)
    {   
        s_len = getline(&str, &len, stdin); 

        if(s_len == -1)
        {
            free(str);
            handle_error("getline");
        }
        if(isExit(str))
        {
            cancel_transport_thread(pth_transport);
            ERROR_MS(printf("Server(%s) stopped!\n", SERVER_NAME));
            break;
        }
    }

    delete_shm(SERVER_NAME);
    sem_del(SEM_ID, SERVER_NAME);
    exit(EXIT_SUCCESS);
}