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
    int opt, client_fd;
    char host[16] = {0};
    int port = -1;
    struct sockaddr_in serv_addr, client_addr;

    while ((opt = getopt(argc, argv, "h:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("server address: %s\n", optarg);
            char* ind = index(optarg, (int)':');
            if (ind == NULL){port = -1; break;}
            strncpy(host, optarg, (int)(ind-optarg));
            port = atoi(optarg+(ind-optarg)+1);
            break;

        default:
            break;
        }
    }
    if(port == -1){
        fprintf(stderr, "Usage: %s -h 127.*.*.*:port\n", argv[0]);
        exit(EXIT_FAILURE); 
    }

    /*struct hostent *he = gethostbyname("serv1");
    if(he == NULL){
        perror("gethostbyname");
    }
    printf("my int ip: %d\n", inet_addr("127.0.1.5"));
    printf("ip1: %d\n", ntohl((*((struct in_addr*)he->h_addr_list[0])).s_addr));
    printf("ip: %s\n", inet_ntoa(*((struct in_addr*)he->h_addr_list[0])));

    struct in_addr ip_addr;
    ip_addr.s_addr = ntohl((*((struct in_addr*)he->h_addr_list[0])).s_addr);
    printf("revert ip: %s\n", inet_ntoa(ip_addr));*/

    if((FD = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        serv_exit(-1, "socket");
    }
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host);
    serv_addr.sin_port = htons(port);
    // if(setsockopt(FD, SOL_IP, IP_TRANSPARENT, &(int){1}, sizeof(int)) == -1){
    //     serv_exit(FD, "IP_TRANSPARENT");
    // }
    
    if(bind(FD, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) == -1){
        serv_exit(FD, "bind");
    }
    printf("server (%s:%d) binding successful!\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

    if(listen(FD, 5) == -1){
        serv_exit(FD, "listen");
    }

    printf("Server waiting for a client connection...\n");
    socklen_t len = sizeof(client_addr); 
    if((client_fd = accept(FD, (struct sockaddr*)&client_addr, &len)) == -1){
        serv_exit(FD, "accept");
    }

    if(getpeername(client_fd, (struct sockaddr*)&client_addr, &len) == -1){
        serv_exit(FD, "getsockname");
    }
    printf("client (%s:%d) accepted!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char buf[256]; 
    if(recv(client_fd, buf, 256, 0)==-1){
        serv_exit(FD, "recv");
    }
    printf("msg from client(%s:%d)>>  %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);

    memset(buf, 0, 256);
    strcpy(buf, "Accept - OK!\n Send msg - OK!");
    if(send(client_fd, buf, 256, 0) == -1){
        serv_exit(FD, "send");
    }

    puts("BAY, server close all desriptors!");
    close(FD);
    close(client_fd);
}