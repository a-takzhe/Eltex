
#include "module/reciever.h"

void unlinc_all()
{
    if(mq_unlink("/alex") == -1){
        ERROR_MS(handle_error("mq_unlink alex error"));
    }
    if(mq_unlink("/anton") == -1){
        ERROR_MS(handle_error("mq_unlink anton error"));
    }
    if(mq_unlink("/mark") == -1){
        ERROR_MS(handle_error("mq_unlink mark error"));
    }
}

int isExit(char* str)
{
    return (strcmp(str, "exit") == 0 || strstr(str, "exit") != NULL);
}

int uEscape(char* str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if(str[i]==27 || str[i]==1) return 1;
    }
    return 0;
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
                strncpy(SERV_NAME+1, optarg, 63);
                break;
            default:
                break;
        }
    }
    if(SERV_NAME[1] == 0){
        strncpy(SERV_NAME+1, "test-server", 63);
    }
    SERV_NAME[0] = '/';

    printf("statrt init %s Server...\n",SERV_NAME);
    serv_mq_open(SERV_NAME, &Q_SERV_ID);   

    err = pthread_create(&pth, NULL, my_recv, NULL);
    if (err != 0)
        handle_error_en(err, "pthread_create");

    while (1)
    {   
        s_len = getline(&str, &len, stdin); 

        if(s_len == -1){
            free(str);
            handle_error("getline");
        }
        if(uEscape(str)){
            puts("don't use escape sequences");
            continue;
        }   
        if(isExit(str)){
            err = pthread_cancel(pth);
            if(err != 0)
                handle_error_en(err, "pthread_cancel");
            break;
        }
    }

    serv_mq_unlinq(SERV_NAME, Q_SERV_ID);
    unlinc_all();
    exit(EXIT_SUCCESS);
}