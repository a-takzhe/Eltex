#ifndef CNT_CLI_H
#define CNT_CLI_H

#include "./communication.h"
#include "./synclayer.h"

void create_my_ipc(const char* name);
int attach_to_server(const char* name);
void* listen_server();

void close_server_ipc();
void delete_my_ipc();

#endif