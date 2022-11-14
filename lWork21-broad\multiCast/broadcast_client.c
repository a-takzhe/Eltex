#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


int main (int argc, char** argv)
{
    int fd;
    struct sockaddr_in bAddr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket is created!\n");

    bAddr.sin_port = htons(8000);
    bAddr.sin_addr.s_addr = inet_addr("192.168.56.255");
    bAddr.sin_family = AF_INET;

    printf("addr: (%s:%d)\n", inet_ntoa(bAddr.sin_addr), ntohs(bAddr.sin_port));

    if(bind(fd, (struct sockaddr*)&bAddr, sizeof(struct sockaddr_in)) == -1){
        perror("bind");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket is binded!\n");

    char buf[256]={0};
    int len = sizeof(struct sockaddr_in);
    if(recvfrom(fd, buf, 256, 0, (struct sockaddr*)&bAddr, &len) == -1){
        perror("recvfrom");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("msg >> %s\n", buf);
    
    close(fd);
    exit(EXIT_SUCCESS);
}