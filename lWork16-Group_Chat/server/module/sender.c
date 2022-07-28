#include "sender.h"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MSG;
    attr->mq_msgsize = sizeof(package);
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

int add_user(package pack)
{
    struct mq_attr attr;
    package *npack = (package*)calloc(sizeof(package),1);

    set_attr(&attr);

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id == 0){
            USERS[i].active = 1;
            strncpy(USERS[i].name, pack.message, MAX_USER_NAME);
            USERS[i].uid = i;

            USERS[i].q_id = mq_open(USERS[i].name, O_WRONLY, 0777, &attr);
            if(USERS[i].q_id == -1){
                free(npack);
                ERROR_MS(handle_error("Q_USR_ID mq_open error"));
            }

            npack->u_id = i;
            strncpy(npack->message, "Accept-OK", MAX_MSG_SIZE);
            char* bufer = (char*)npack;
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 3) == -1)
            {
                free(npack);
                ERROR_MS(handle_error("mq_send error"));   
            }
            return i;
        }
    }
    free(npack);
    return -1;    
}

int snd_old_to_new(package* pack, int uid)
{
    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != uid)
        {
            package *npack = (package*)malloc(sizeof(package));
            strncpy(npack->message, USERS[i].name, MAX_USER_NAME);
            npack->u_id = USERS[i].uid;
            char* bufer = (char*)npack;

            printf("sennd %s\n", npack->message);
            if(mq_send(USERS[uid].q_id, bufer, sizeof(package), 2) == -1)
            {
                free(npack);
                ERROR_MS(handle_error("mq_send error"));   
            }
            free(npack);
        }
    }
    
}

int snd_new_to_old(package* pack, int uid)
{
    pack->u_id = uid;
    char* bufer = (char*)pack;

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != uid)
        {
            printf("sennd to %s\n", USERS[i].name);
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 2) == -1)
            {
                ERROR_MS(handle_error("mq_send error"));   
            }
        }
    }
}

int send_msg(package* pack)
{
    // for(int i = 0; i < MAX_USER; i++){
    //     if(USERS[i].q_id != pack->u_id){
    //         pack->u_id = i;
    //         break;;
    //     }
    // }

    char* bufer = (char*)pack;

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != pack->u_id)
        {
            printf("sennd msg to %s\n", USERS[i].name);
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 1) == -1)
            {
                ERROR_MS(handle_error("mq_send error"));   
            }
        }
    }
}

