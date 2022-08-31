#include "reciever.h"


void serv_mq_open(const char* s_name)
{
    puts("Create server queue...");
    struct mq_attr attr;
    set_attr(&attr);

    Q_SERV_ID = mq_open(s_name, O_RDONLY | O_CREAT, 0777, &attr);
    if(Q_SERV_ID == -1){
        handle_error("mq_open error");
    }
    printf("Server queue id = %d\n", Q_SERV_ID);
}

void serv_mq_unlinq(const char* s_name, mqd_t mq_id)
{
    if(mq_unlink(s_name) == -1){
        handle_error("Q_SERV_ID mq_unlink error");
    }
    printf("Queue (%d) is deleted!\n", mq_id);
}

// FUNCTION READ MESSAGE FROM CONNECTING USERS AND
// SEND MESSAGE OTHER CONNECTING USERS
void* my_recv()
{
    uint prior;
    
    while(1)
    { 
        package* pack;
        char buffer[sizeof(package)];
        int len, uid;

        // STAT_MS(puts("Waiting for a message..."));
        if((len = mq_receive(Q_SERV_ID, buffer, sizeof(buffer), &prior)) == -1){
            handle_error("mq_receive error");
        }

        pack = (package*)buffer;
        if(prior == 1)
        {
            printf("user %s send msg: %s\n", USERS[pack->u_id].name, pack->message);
            send_msg(pack);
        }
        else if(prior == 2)
        {
            STAT_MS(printf("user:%s try attach to server\n", pack->message));
            
            if((uid = add_user(*pack)) == -1){
                ERROR_MS(puts("MAX count of user"));
            }
            snd_new_to_old(pack, uid);
            snd_old_to_new(uid);                        
            
            STAT_MS(printf("user:%s attach to server with (%d)mq_id and (%d)uid\n", USERS[uid].name, USERS[uid].q_id, uid));
        }
        else if(prior == 3)
        {
            STAT_MS(printf("user %s disconnected!\n"));
            disconnect_user(pack);
        }
        else
        {
            ERROR_MS(puts("Unrecognize message!!"));
        }
    } 
}


