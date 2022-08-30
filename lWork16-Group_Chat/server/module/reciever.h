#ifndef S_RECIEVER_H
#define S_RECIEVER_H

#include "data.h"
#include "sender.h"

void serv_mq_open(const char* s_name);
void serv_mq_unlinq(const char* s_name, mqd_t mq_id);
void* my_recv();

#endif