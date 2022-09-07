
// #include "module/reciever.h"
#include "module/sem_class.h"
#include "module/shm_class.h"

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
    pthread_t pth;
    
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
        //strncpy(SERV_NAME+1, "test-server", 63);
        puts("please, use option '-n' for set server name");
        exit(EXIT_FAILURE);
    }
    SERVER_NAME[0] = '/';

    //initialization message queue 
    STAT_MS(printf("Statrt init Server (%s)...",SERVER_NAME));
    SHM_PTR = create_server_shm(SERVER_NAME);
    STAT_MS(puts("Server shm created!\nCreate server semophore..."));
    SEM_ID = create_server_sem(SERVER_NAME);
    STAT_MS(puts("Server semophore created"));


    // //thread for communication betwin users  
    // err = pthread_create(&pth, NULL, my_recv, NULL);
    // if (err != 0){
    //     handle_error_en(err, "pthread_create");
    // }

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
            // err = pthread_cancel(pth);
            // if(err != 0){
            //     handle_error_en(err, "pthread_cancel");   
            // }
            ERROR_MS(printf("Server(%s) stopped!\n", SERVER_NAME));
            break;
        }
    }

    // serv_mq_unlinq(SERVER_NAME, Q_SERV_ID);
    delete_shm(SERVER_NAME);
    sem_del(SEM_ID);
    exit(EXIT_SUCCESS);
}