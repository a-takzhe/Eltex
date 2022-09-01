#include "queue.h"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MQ_MSG;
    attr->mq_msgsize = sizeof(package);
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

void usr_mq_open()
{
    struct mq_attr attr;
    set_attr(&attr);
    printf("Create client(%s) queue...\n", LOGIN);
    
    Q_USR_ID = mq_open(LOGIN, O_RDONLY | O_CREAT | O_EXCL, 0666, &attr);
    if(Q_USR_ID == -1){
        handle_error("Q_USR_ID mq_open error");
    }
    printf("Client queue id = %d\n", Q_USR_ID);
}

void usr_mq_unlinq()
{
    if(mq_unlink(LOGIN) == -1){
        handle_error("mq_unlink Q_USR_ID error");
    }
    printf("Queue (%d) is deleted!\n", Q_USR_ID);

    //deattach from server
    package *pack = (package*)malloc(sizeof(package));
    char* bufer = (char*)pack;
    pack->u_id = MY_UID;
    strncpy(pack->message, LOGIN, MAX_USER_NAME);
    if(mq_send(Q_SERV_ID, bufer, sizeof(package), 3) == -1){
        free(pack);
        handle_error("mq_send to server error");   
    }
    if(mq_close(Q_SERV_ID) == -1){
        handle_error("mq_close Q_SERV_ID error");
    }
    printf("Server queue (%d) is closed!\n", Q_SERV_ID);
    
}

int attach_to_server()
{
    uint prior;
    struct mq_attr attr;
    package *pack = (package*)malloc(sizeof(package));
    set_attr(&attr);
    
    //open server queue
    printf("Create server(%s) queue...\n", SERV_NAME);
    if((Q_SERV_ID = mq_open(SERV_NAME, O_WRONLY, 0666, &attr)) == -1){
        ERROR_MS(handle_error("Q_SERV_ID mq_open error"));
    }
    printf("Server queue id = %d\n", Q_SERV_ID);

    //send attached pack
    strncpy(pack->message, LOGIN, MAX_USER_NAME);
    // pack->u_id = Q_USR_ID;
    char* bufer = (char*)pack;

    if(mq_send(Q_SERV_ID, bufer, sizeof(package), 2) == -1){
        free(pack);
        handle_error("mq_send to server error");   
    }
    free(pack);        
}

int send_msg(char* msg)
{
    package *pack = (package*)malloc(sizeof(package));
    char* bufer = (char*)pack;

    strncpy(pack->message, msg, MAX_MSG_SIZE);
    pack->u_id = MY_UID;

    if(mq_send(Q_SERV_ID, bufer, sizeof(package), 1) == -1){
        free(pack);
        handle_error("mq_send msg to server error");   
    }
    free(pack); 
    return 1;
}

void* listen_server()
{
    uint prior;
    int i=0;
    while(1)
    { 
        package* pack;
        char buffer[sizeof(package)];
        int len;

        // STAT_MS(puts("Waiting for a message..."));
        if((len = mq_receive(Q_USR_ID, buffer, sizeof(buffer), &prior)) == -1)
        {
            handle_error("mq_receive from server error");
        }

        pack = (package*)buffer;
        if(prior == 1)
        {
            sync_add_msg(pack->message, pack->u_id);
        }
        else if(prior == 2)
        {
            sync_add_usr(pack->message, pack->u_id); 
        }
        else if(prior == 3)
        {
            //printf("%s\nMY_UID(%d)\n",pack->message, pack->u_id); 
            MY_UID = pack->u_id; 
            if(MY_UID == -1)
            {
                ERROR_MS(puts("Server is full"));
                usr_mq_unlinq();
                exit(EXIT_FAILURE);
            }                  
        }
        else if(prior == 4){
            sync_user_disconnect(pack->u_id);
        }
        i++;
    } 
}
