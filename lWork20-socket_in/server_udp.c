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

int main(int argc, char** argv)
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

    if((FD = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        serv_exit(-1, "socket");
    }
    
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host);
    serv_addr.sin_port = htons(port);
    
    if(bind(FD, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) == -1){
        serv_exit(FD, "bind");
    }
    printf("server (%s:%d) binding successful!\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));


    char buf[256];
    socklen_t len = sizeof(client_addr); 
    if(recvfrom(FD, buf, 256, 0, (struct sockaddr*)&client_addr, &len) == -1){
        serv_exit(FD, "recvfrom");
    }
    // if(getpeername(client_fd, (struct sockaddr*)&client_addr, &len) == -1){
    //     serv_exit(FD, "getsockname");
    // }
    printf("client (%s:%d) send msg >> %s!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);


    memset(buf, 0, 256);
    strcpy(buf, "Recvfom client successe!");
    if(sendto(FD, buf, 256, 0, (struct sockaddr*)&client_addr, len) == -1){
        serv_exit(FD, "sendto");
    }

    puts("BAY, server close all desriptors!");
    close(FD);
    close(client_fd);

}