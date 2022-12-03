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
    mAddr.sin_addr.s_addr = INADDR_ANY;
    mAddr.sin_family = AF_INET;

    printf("addr: (%s:%d)\n", inet_ntoa(mAddr.sin_addr), ntohs(mAddr.sin_port));

    struct ip_mreqn w = {.imr_multiaddr.s_addr = inet_addr("224.0.0.1"),
                         .imr_address = mAddr.sin_addr,
                         .imr_ifindex = 0 };
    if(setsockopt(fd, SOL_IP, IP_ADD_MEMBERSHIP, &w, sizeof(w)) == -1){
        perror("setsockopt");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Option is setting!\n");

    if(bind(fd, (struct sockaddr*)&mAddr, sizeof(struct sockaddr_in)) == -1){
        perror("bind");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket is binded!\n");

    char buf[256]={0};
    int len = sizeof(struct sockaddr_in);
    if(recvfrom(fd, buf, 256, 0, (struct sockaddr*)&mAddr, &len) == -1){
        perror("recvfrom");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("msg >> %s\n", buf);
    
    close(fd);
    exit(EXIT_SUCCESS);
}