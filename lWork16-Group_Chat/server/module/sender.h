#ifndef S_SENDER_H
#define S_SENDER_H

#include "data.h"

void set_attr(struct mq_attr* attr);
int add_user(package pack);
int snd_old_to_new(int uid);
int snd_new_to_old(package* pack, int uid);
int send_msg(package* pack);
int disconnect_user(package* pack)
#endif