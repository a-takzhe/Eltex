#include "reciever.h"


void serv_mq_open(const char* s_name, mqd_t* mq_id)
{
    puts("Create server queue...");
    struct mq_attr attr;
    set_attr(&attr);

    *mq_id = mq_open(s_name, O_RDONLY | O_CREAT, 0777, &attr);
    if(*mq_id == -1){
        ERROR_MS(handle_error("Q_SERV_ID read error"));
    }
    printf("Server queue id = %d\n", *mq_id);
}

void serv_mq_unlinq(const char* s_name, mqd_t mq_id)
{
    if(mq_unlink(s_name) == -1){
        ERROR_MS(handle_error("mq_unlink Q_SERV_ID error"));
    }
    printf("Queue (%d) is deleted!\n", mq_id);
}


void* my_recv()
{
    uint prior;
    
    while(1)
    { 
        package* pack;
        char buffer[sizeof(package)];
        int len, uid;

        // STAT_MS(puts("Waiting for a message..."));
        if((len = mq_receive(Q_SERV_ID, buffer, sizeof(buffer), &prior)) == -1)
        {
            ERROR_MS(handle_error("mq_receive error"));
        }

        pack = (package*)buffer;
        if(prior == 2)
        {
            STAT_MS(printf("user:%s try attach to server\n", pack->message));
            
            if((uid = add_user(*pack)) == -1){
                ERROR_MS(puts("MAX count of user"));
            }
            snd_new_to_old(pack, uid);
            snd_old_to_new(pack, uid);                        
            
            STAT_MS(printf("user:%s attach to server with (%d)mq_id and (%d)uid\n", USERS[uid].name, USERS[uid].q_id, uid));
        }
        else if(prior == 1)
        {
            printf("user %d send msg: %s\n", pack->u_id, pack->message);
            send_msg(pack);
        }
    } 
}


