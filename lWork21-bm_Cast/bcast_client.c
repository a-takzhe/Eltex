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

in_addr_t getbaddr()
{
    int fd;
    in_addr_t addr = -1;
    struct ifreq ifr;
    struct if_nameindex *if_nidxs, *intf;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;

    if_nidxs = if_nameindex();
    if (if_nidxs != NULL )
    {
        for (intf = if_nidxs; intf->if_index != 0 || intf->if_name != NULL; intf++)
        {
            memcpy(ifr.ifr_name, intf->if_name, IFNAMSIZ - 1);
            ioctl(fd, SIOCGIFFLAGS, &ifr); 
            
            if(ifr.ifr_ifru.ifru_flags & IFF_UP && !(ifr.ifr_ifru.ifru_flags & IFF_LOOPBACK))
            {
                ioctl(fd, SIOCGIFBRDADDR, &ifr);
                printf("%s: System IP Address is: %s\n",ifr.ifr_name, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
                addr = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
                break;
            }
        }
        if_freenameindex(if_nidxs);
    }
    close(fd);

    return addr;
}

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
    bAddr.sin_addr.s_addr = getbaddr();
    if(bAddr.sin_addr.s_addr == -1){
        bAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    }
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