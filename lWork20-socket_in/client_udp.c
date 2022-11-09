
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
    int opt, fd;
    char hip[16] = {0}, sip[16]={0};
    int hport = -1, sport = -1;
    struct sockaddr_in serv_addr, client_addr;

    while ((opt = getopt(argc, argv, "h:s:")) != -1)
    {
        char* ind  = NULL;
        switch (opt)
        {
        case 'h':
            printf("my address: %s\n", optarg);
            ind = index(optarg, (int)':');
            if (ind == NULL) break;
            strncpy(hip, optarg, (int)(ind-optarg));
            hport = atoi(optarg+(ind-optarg)+1);
            break;
        case 's':
            printf("server address: %s\n", optarg);
            ind = index(optarg, (int)':');
            if (ind == NULL) break;
            strncpy(sip, optarg, (int)(ind-optarg));
            sport = atoi(optarg+(ind-optarg)+1);
            break;
        default:
            break;
        }
    }
    if(hport == -1 || sport == -1){
        fprintf(stderr, "Usage: %s -h [127.*.*.*:port] -s [server_addr]\n", argv[0]);
        exit(EXIT_FAILURE); 
    }

    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        client_exit(-1, "socket");
    }

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(hip);
    client_addr.sin_port = htons(hport);

    if(bind(fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1){
        client_exit(fd, "bind");
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(sip);
    serv_addr.sin_port = htons(sport);

    puts("Connected to server...");
    int len = sizeof(serv_addr);
    if(connect(fd, (const struct sockaddr*)&serv_addr, len) == -1){
        client_exit(fd, "connect");
    }

    char buf[256];
    strcpy(buf, "Hi server! This is UDP DGRAM!");
    printf("sendto server(%s:%d)>> %s\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port), buf);
    if(send(fd, buf, 256, 0) == -1){
        client_exit(fd, "send");
    }
    puts("Send successe!"); 

    memset(buf, 0, 256);
    if(recv(fd, buf, 256, 0)==-1){
        client_exit(fd, "recv");
    }
    printf("msg from server(%s:%d)>>  %s\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port), buf);

    puts("BAY, client close all desriptors!");
    close(fd);
}