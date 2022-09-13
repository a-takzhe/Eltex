#ifndef _DATA_SERV_H
#define _DATA_SERV_H

#include "../../common/common.h"

int   SEM_ID;
int   PROJ_ID;
void* SHM_PTR;
char  SERVER_NAME[64];
user  USERS[MAX_USERS]; 

void init_user_arr();
int can_add_user();
int add_user(const char* name, int sem_id, void* ptr);
void del_user(int uid);

#endif