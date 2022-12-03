#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

int main (int argc, char** argv)
{
    int fd;
    struct sockaddr_in mAddr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Socket is created!\n");
    
    mAddr.sin_port = htons(8000);
    mAddr.sin_addr.s_addr = inet_addr("224.0.0.1");
    mAddr.sin_family = AF_INET;

    char buf[256]={"test multicast message!"};
    if(sendto(fd, buf, 256, 0, (struct sockaddr*)&mAddr, sizeof(struct sockaddr_in)) == -1){
        perror("snedto");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Message is sended!\n");

    close(fd);
    exit(EXIT_SUCCESS);
}