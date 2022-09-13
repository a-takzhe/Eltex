#ifndef WWC_H
#define WWC_H

#include "data.h"
#include "../../common/sem_class.h"
#include "../../common/shm_class.h"

int send_message(int uid_to, int uid_from, const char* mes, int status);
int send_to_other_clients(int uid, const char* mes, int status);
int client_attach(package pack);
int client_deattach(package pack);
int all_client_deattach();

#endif