#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define client_exit(fd, func_name) \
        do{perror(func_name); close(fd); exit(EXIT_FAILURE);}while(0)

int main (int argc, char *argv[])
{
    struct sockaddr_in serv_addr, client_addr;
    int fd;

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        client_exit(-1, "socket");
    }

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.2.2");
    serv_addr.sin_port = htons(atoi("8080"));

    // if(setsockopt(fd, SOL_IP, IP_FREEBIND, &(int){1}, sizeof(int)) == -1){
    //     client_exit(fd, "setsockopt");
    // }
    if(bind(fd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr)) == -1){
        client_exit(fd, "bind");
    }

    printf("client ip: %s\n", inet_ntoa(client_addr.sin_addr));

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = atoi(argv[2]);

    int len = sizeof(struct sockaddr_in);
    if(connect(fd, (const struct sockaddr*)&serv_addr, len) == -1){
        client_exit(fd, "connect");
    }

    printf("client ip: %s\n", inet_ntoa(client_addr.sin_addr));
}