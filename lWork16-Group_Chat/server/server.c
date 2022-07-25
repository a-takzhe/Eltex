
#include "../common.h"

char SERV_NAME[64];
static int USER_ID;

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MSG;
    attr->mq_msgsize = MAX_MSG_SIZE+sizeof(int);
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

int main(int argc, char* argv[])
{
    int opt;
    mqd_t server_mq;
    uint prior;
    struct mq_attr attr;
    
    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
            case 'n':
                strncpy(SERV_NAME+1, optarg, 64);
                break;
            default:
                break;
        }
    }
    if(SERV_NAME[1] == 0){
        strncpy(SERV_NAME+1, "test-setrve", 64);
    }
    SERV_NAME[0] = '/';
    printf("statrt init %s Server...\n",SERV_NAME);
    STAT_MS(puts("Attr init..."));
    set_attr(&attr);  

    STAT_MS(puts("Create queue.."));

    
    server_mq = mq_open(SERV_NAME, O_RDONLY | O_CREAT, 0777, &attr);
    if(server_mq == -1){
        ERROR_MS(handle_error("server_mq read error"));
    }
    printf("Server queue id = %d\n", server_mq);


    while(1)
    { 
        package* pack;
        char buffer[attr.mq_msgsize];
        int len;

        STAT_MS(puts("Waiting for a message..."));
        if((len = mq_receive(server_mq, buffer, sizeof(buffer), &prior)) == -1)
        {
            ERROR_MS(handle_error("mq_receive error"));
        }
        else
        {
            pack = (package*)buffer;
            if(prior == 2){
                printf("user %s attach to server\n", pack->message);
            }
            else if(prior == 1){
                printf("user %s attach to server\n", pack->message);
            }
        }
    }    


    if(mq_unlink(SERV_NAME) == -1){
        ERROR_MS(handle_error("mq_unlink error"));
    }
    printf("Queue (%d) is deleted!\n", server_mq);

    exit(EXIT_SUCCESS);
}