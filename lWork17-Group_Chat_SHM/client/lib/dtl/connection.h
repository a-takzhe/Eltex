#ifndef CNT_CLI_H
#define CNT_CLI_H

#include "./communication.h"
#include "./synclayer.h"

void create_my_ipc(const char* name);
void attach_to_server_ipc(const char* name);
void* listen_server();
int attach_to_server();

void close_server_ipc();
void delete_my_ipc();

#endif