#include "./lib/gui/handler.h"
#include "./lib/dtl/connection.h"


int main(int argc, char* argv[])
{
    srand ( time(NULL) ); 
    setlocale(LC_ALL, "");
    mutex_init();
    ID_LAST_MSG = -1;
   
    int opt;
    
    
    while ((opt = getopt(argc, argv, "s:l:")) != -1)
    {
        switch (opt)
        {
            case 's':
                strncpy(SERV_NAME+1, optarg, 63);
                break;
            case 'l':
                strncpy(LOGIN+1, optarg, MAX_USER_NAME-1);
                break;
            default:
                printf("unknown key %c!\n", opt);
                exit(EXIT_FAILURE);
                break;
        }
    }
    if(SERV_NAME[1] == 0){
        // strncpy(SERV_NAME+1, "test-setrve", 63);
        puts("please, use option '-s' for set server name");
        exit(EXIT_FAILURE);
    }
    if(LOGIN[1] == 0){
        // strncpy(LOGIN+1, "alex", MAX_USER_NAME-1);
        puts("please, use option '-l' for set login");
        exit(EXIT_FAILURE);
    }
    LOGIN[0]='/';
    SERV_NAME[0]='/';
    

    init_user_arr();
    create_my_ipc(LOGIN);
    attach_to_server_ipc(SERV_NAME);
    if(attach_to_server() == -1)
    {
        close_server_ipc();
        delete_my_ipc();
        exit(EXIT_FAILURE);
    }

    init();

    int err = pthread_create(&pth_listener, NULL, listen_server, NULL);
    if (err != 0) handle_error_en(err, "pthread_create");

    if(h_main() == -1){
        write_message(LOGIN, 3);
    }
    wend();
    close_server_ipc();
    delete_my_ipc();
    exit(EXIT_SUCCESS);
}