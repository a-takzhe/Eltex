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

    int w = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &w, sizeof(w)) == -1){
        perror("setsockopt");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Option is setting!\n");

    char buf[256]={"test broadcast message!"};
    if(sendto(fd, buf, 256, 0, (struct sockaddr*)&bAddr, sizeof(struct sockaddr_in)) == -1){
        perror("snedto");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Message is sended!\n");

    close(fd);
    exit(EXIT_SUCCESS);
}