#ifndef _SYNC_LAYER_H
#define _SYNC_LAYER_H

#include "../data/store.h"
#include "../gui/form.h"

pthread_mutex_t usr_mutex;
pthread_mutex_t msg_mutex;

void mutex_init();
int sync_add_msg(char* text, int uid);
int sync_add_usr(char* name, int uid);

#endif