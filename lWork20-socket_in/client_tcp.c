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

    printf("desired client addr: 192.168.123.1:%d\n", atoi("8888"));

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("192.168.123.1");
    client_addr.sin_port = htons(atoi("8888"));

    if(setsockopt(fd, SOL_IP, IP_FREEBIND, &(int){1}, sizeof(int)) == -1){
        client_exit(fd, "IP_FREEBIND");
    }
    if(setsockopt(fd, SOL_IP, IP_TRANSPARENT, &(int){1}, sizeof(int)) == -1){
        client_exit(fd, "IP_TRANSPARENT");
    }
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &(int){1}, sizeof(int)) == -1){
        client_exit(fd, "SO_REUSEADDR|SO_REUSEPORT");
    }
    if(bind(fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) == -1){
        client_exit(fd, "bind");
    }

    printf("client addr after bind: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = atoi(argv[2]);

    int len = sizeof(client_addr);
    if(connect(fd, (const struct sockaddr*)&serv_addr, len) == -1){
        client_exit(fd, "connect");
    }

    if(getsockname(fd, (struct sockaddr*)&client_addr, &len) == -1){
        client_exit(fd, "getsockname");
    }
    
    printf("client addr after connect: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    close(fd);
}