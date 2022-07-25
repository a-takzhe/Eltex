#include <stdio.h>
#include "./lib/handler.h"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MSG;
    attr->mq_msgsize = MAX_MSG_SIZE;
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

int main(int argc, char* argv[])
{
    srand ( time(NULL) ); 
    setlocale(LC_ALL, "");

    mqd_t server_mq;
    struct mq_attr attr;
    uint prior;
    char *bufer = (char*)malloc(sizeof(package));
    puts("dasd1");
    
    package *pack = (package*)malloc(sizeof(package));
    pack->q_id = 4;
    strcpy(pack->message, "ernesto");
    puts("dasd");
    bufer = (char*)pack;
    printf("::%s\n", bufer);

    

    server_mq = mq_open("/lala", O_WRONLY, 0777, &attr);
    if(server_mq == -1){
        ERROR_MS(handle_error("server_mq read error"));
    }
    printf("Server queue id = %d\n", server_mq);

    STAT_MS(printf("Sending a message to queue (%d)\n", server_mq));
    if(mq_send(server_mq, bufer, strlen(bufer), 2) == -1)
    {
        ERROR_MS(handle_error("mq_send error"));   
    }
    STAT_MS(puts("Message is send"));
    mq_close(server_mq);

    // init();
    
    // add_usr("alex", -1);
    // add_usr("tomas",-1);
    // add_usr("luke", -1);
    // update_usr_area();

    // add_msg("Hello friends", 0);
    // add_msg("Hi", 1);
    // add_msg("Hello alex", 2);
    // add_msg("Fuck you", -1);
    // add_msg("Fuck you too", 0);
    // update_msg_area();

    // h_main();
    // wend();
    return 0;
}