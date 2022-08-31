#include "sender.h"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = MAX_MSG;
    attr->mq_msgsize = sizeof(package);
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

// Возвращает ИД пользователя в списке пользователей иначе -1
int add_user(package pack)
{
    char msg[50];
    struct mq_attr attr;
    char* bufer;
    set_attr(&attr);
    package *npack = (package*)calloc(sizeof(package),1);

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id == 0)
        {
            USERS[i].uid = i;
            USERS[i].active = 1;
            strncpy(USERS[i].name, pack.message, MAX_USER_NAME);

            USERS[i].q_id = mq_open(USERS[i].name, O_WRONLY, 0777, &attr);
            if(USERS[i].q_id == -1){
                free(npack);
                sprintf(msg, "mq_open for user %s error", pack.message);
                handle_error(msg);
            }

            npack->u_id = i;
            strncpy(npack->message, "Accept-OK", MAX_MSG_SIZE);
            bufer = (char*)npack;
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 3) == -1)
            {
                free(npack);
                sprintf(msg, "mq_send to user %s error", pack.message);
                handle_error(msg);   
            }
            return i;
        }
    }
    free(npack);
    return -1;    
}

int snd_old_to_new(int uid)
{
    package *npack = (package*)malloc(sizeof(package));
    char* bufer = (char*)npack;

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != uid)
        {        
            strncpy(npack->message, USERS[i].name, MAX_USER_NAME);
            npack->u_id = USERS[i].uid;

            printf("sennd %s nickname to %s \n", npack->message, USERS[uid].name);
            if(mq_send(USERS[uid].q_id, bufer, sizeof(package), 2) == -1)
            {
                free(npack);
                ERROR_MS(handle_error("mq_send error"));   
            }
        }
    }
    free(npack);
    return 1;
}

//send nickname and user id in the list to already connected users
int snd_new_to_old(package* pack, int uid)
{
    char msg[50];
    pack->u_id = uid;
    char* bufer = (char*)pack;

    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != uid)
        {
            printf("sennd to %s that (%s) connected\n", USERS[i].name, pack->message);
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 2) == -1)
            {
                sprintf(msg, "mq_send to %s error!", USERS[i].name);
                handle_error(msg);   
            }
        }
    }
    return 1;
}

int send_msg(package* pack)
{
    char* bufer = (char*)pack;
    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != pack->u_id)
        {
            printf("sennd message from (%s) to (%s)\n",USERS[pack->u_id].name, USERS[i].name);
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 1) == -1)
            {
                handle_error("mq_send error!");   
            }
        }
    }
    return 1;
}

int disconnect_user(package* pack)
{
    char* bufer = (char*)pack;
    for (int i = 0; i < MAX_USER; i++)
    {
        if(USERS[i].q_id != 0 && i != pack->u_id)
        {
            printf("sennd to %s that (%s) disconnected\n",USERS[i].name, pack->message);
            if(mq_send(USERS[i].q_id, bufer, sizeof(package), 4) == -1)
            {
                handle_error("mq_send error!");   
            }
        }
    }

    //clear USERS
    USERS[pack->u_id].q_id = 0;
    USERS[pack->u_id].uid  = 0;
    USERS[pack->u_id].name[0] = '\0';
    
    return 1;
}

