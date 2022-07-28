#ifndef S_QUEUE_H
#define S_QUEUE_H

#include "synclayer.h"


void set_attr(struct mq_attr* attr);

void usr_mq_open();
void usr_mq_unlinq();
int  attach_to_server();
int send_msg(char* msg);
void* listen_server();
#endif