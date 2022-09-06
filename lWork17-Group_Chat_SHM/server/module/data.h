#ifndef _DATA_SERV_H
#define _DATA_SERV_H

#include "../../common.h"

char  SERVER_NAME[64];
mqd_t Q_SERV_ID;
user  USERS[MAX_USERS]; 

#endif