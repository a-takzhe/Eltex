#include "queue.h"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MSG;
    attr->mq_msgsize = sizeof(package);
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

void usr_mq_open()
{
    struct mq_attr attr;
    set_attr(&attr);
    printf("Create client(%s) queue...\n", LOGIN);
    
    Q_USR_ID = mq_open(LOGIN, O_RDONLY | O_CREAT | O_EXCL, 0777, &attr);
    if(Q_USR_ID == -1){
        ERROR_MS(handle_error("Q_USR_ID read error"));
    }
    printf("Client queue id = %d\n", Q_USR_ID);
}

void usr_mq_unlinq()
{
    if(mq_unlink(LOGIN) == -1){
        ERROR_MS(handle_error("mq_unlink Q_USR_ID error"));
    }
    printf("Queue (%d) is deleted!\n", Q_USR_ID);
}

int attach_to_server()
{
    struct mq_attr attr;
    package *pack = (package*)malloc(sizeof(package));
    set_attr(&attr);
    
    //open server queue
    printf("Create server(%s) queue...\n", SERV_NAME);
    if((Q_SERV_ID = mq_open(SERV_NAME, O_WRONLY, 0666, &attr)) == -1){
        ERROR_MS(handle_error("Q_SERV_ID read error"));
    }
    printf("Server queue id = %d\n", Q_SERV_ID);

    //send attached pack
    strncpy(pack->message, LOGIN, MAX_USER_NAME);
    pack->u_id = Q_USR_ID;
    char* bufer = (char*)pack;

    if(mq_send(Q_SERV_ID, bufer, sizeof(package), 2) == -1){
        free(pack);
        ERROR_MS(handle_error("mq_send error"));   
    }
    free(pack);        
}

int send_msg(char* msg)
{
    package *pack = (package*)malloc(sizeof(package));
    strncpy(pack->message, msg, MAX_MSG_SIZE);
    pack->u_id = MY_UID;
    char* bufer = (char*)pack;

    if(mq_send(Q_SERV_ID, bufer, sizeof(package), 1) == -1){
        free(pack);
        ERROR_MS(handle_error("mq_send error"));   
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
            ERROR_MS(handle_error("mq_receive error"));
        }

        pack = (package*)buffer;
        if(prior == 2)
        {
            // STAT_MS(printf("user %s attach to server with (%d)uid\n", pack->message, pack->u_id));      
            sync_add_usr(pack->message, pack->u_id); 
        }
        if(prior == 3)
        {
            // STAT_MS(printf("%s MY_UID:%d\n", pack->message, pack->u_id)); 
            MY_UID = pack->u_id;                   
        }
        else if(prior == 1)
        {
            // printf("user %s attach to server\n", pack->message);
            sync_add_msg(pack->message, pack->u_id);
        }
        i++;
    } 
}
