#ifndef TRANS_TH_H
#define TRANS_TH_H

#include "work_with_client.h"

void start_transport_thread(pthread_t* pth);
void cancel_transport_thread(pthread_t pth);
void* main_transport_func();

#endif