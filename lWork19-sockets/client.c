#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define server_name "/tmp/stream_serv"
#define client_exit(fd, fname, func_name) \
        do{perror(func_name); close(fd); unlink(fname); exit(EXIT_FAILURE);}while(0)

int SERV_FD;


void simple_action(int signum)
{
    puts("");
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    struct sigaction act, old_act;
    act.sa_handler = &simple_action;
    if(sigaction(SIGINT, &act, &old_act) == -1)
    {
        perror("sigaction!");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un serv, client;
    int SERV_FD = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(SERV_FD == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&serv, 0, sizeof(struct sockaddr_un));
    serv.sun_family = AF_LOCAL;
    strncpy(serv.sun_path, server_name, sizeof(serv.sun_path)-1);

    socklen_t len = sizeof(struct sockaddr_un);
    connect(SERV_FD, (struct sockaddr*)&serv, len);

    char buf[128] = "Hello server! I`m client\0";
    send(SERV_FD, buf, 128, 0);
    //memset(&serv, 0, sizeof(struct sockaddr_un));
    recv(SERV_FD, buf, 128, 0);
    sleep(100);
    printf("Message from server: \n\t%s\n", buf);

    close(SERV_FD);
}