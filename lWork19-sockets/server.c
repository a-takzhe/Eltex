#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define socket_name "/tmp/stream_serv"
#define serv_exit(fd, fname, func_name) \
        do{perror(func_name); close(fd); unlink(fname); exit(EXIT_FAILURE);}while(0)

int SERV_FD;

void simple_action(int signum)
{
    puts("");
    close(SERV_FD);
    unlink(socket_name);
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
    strncpy(serv.sun_path, socket_name, sizeof(serv.sun_path)-1);
    
    if(bind(SERV_FD, (struct sockaddr *)&serv, sizeof(const struct sockaddr_un)) == -1){
        serv_exit(SERV_FD, socket_name, "bind");
    }
    
    if(listen(SERV_FD, 5) == -1){
        serv_exit(SERV_FD, socket_name, "listen");
    }

    socklen_t len = sizeof(struct sockaddr_un);
    int client_fd = accept(SERV_FD, (struct sockaddr*)&client, &len);
    if(client_fd == -1){
        serv_exit(SERV_FD, socket_name, "accept");
    }

    char buf[128];
    if(recv(client_fd, buf, 128, 0) == -1){
        serv_exit(SERV_FD, socket_name, "recv"); 
    }
    printf("Message from client: \n\t%s\n", buf);

    if(send(client_fd, "Hello client! I`m server\0", 128, 0) == -1){
        serv_exit(SERV_FD, socket_name, "send"); 
    }
    sleep(100);
    close(client_fd);
    close(SERV_FD);
    unlink(socket_name);
    //int client_fd = accept(fd, &client, );

}