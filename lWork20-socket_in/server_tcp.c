#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int FD; 

#define serv_exit(fd, func_name) \
        do{perror(func_name); close(fd); exit(EXIT_FAILURE);}while(0)

int main (int argc, char *argv[])
{
    int client_fd;
    struct sockaddr_in serv_addr, client_addr;

    // struct hostent *he = gethostbyname("serv1");
    // if(he == NULL){
    //     perror("gethostbyname");
    // }
    // printf("my int ip: %d\n", inet_addr("127.0.1.5"));
    // printf("ip1: %d\n", ntohl((*((struct in_addr*)he->h_addr_list[0])).s_addr));
    // printf("ip: %s\n", inet_ntoa(*((struct in_addr*)he->h_addr_list[0])));

    // struct in_addr ip_addr;
    // ip_addr.s_addr = ntohl((*((struct in_addr*)he->h_addr_list[0])).s_addr);
    // printf("revert ip: %s\n", inet_ntoa(ip_addr));

    if (argc != 3) {
        fprintf(stderr, "Usage: %s host(127.*.*.*) port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if((FD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        serv_exit(-1, "socket");
    }
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = atoi(argv[2]);
    if(setsockopt(FD, SOL_IP, IP_TRANSPARENT, &(int){1}, sizeof(int)) == -1){
        serv_exit(FD, "IP_TRANSPARENT");
    }
    
    if(bind(FD, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) == -1){
        serv_exit(FD, "bind");
    }
    if(listen(FD, 5) == -1){
        serv_exit(FD, "listen");
    }

    socklen_t len = sizeof(client_addr); 
    if((client_fd = accept(FD, (struct sockaddr*)0, (int)0)) == -1){
        serv_exit(FD, "accept");
    }
        printf("server ip: %s\n", inet_ntoa(serv_addr.sin_addr));


    if(getpeername(client_fd, (struct sockaddr*)&client_addr, &len) == -1){
        serv_exit(FD, "getsockname");
    }
    // if(getsockname(client_fd, (struct sockaddr*)&client_addr, &len) == -1){
    //     serv_exit(FD, "getsockname");
    // }
    printf("client addr: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    close(FD);
    close(client_fd);
}