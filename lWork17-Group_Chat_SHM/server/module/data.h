#ifndef _DATA_SERV_H
#define _DATA_SERV_H

#include "../../common.h"

#define PROJ_ID  1
#define SEM_PATH "./semaphores/sem-"

int   SEM_ID;
void* SHM_PTR;
char  SERVER_NAME[64];
user  USERS[MAX_USERS]; 

#endif