#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>


#define client_exit(fd, func_name) \
        do{perror(func_name); close(fd); exit(EXIT_FAILURE);}while(0)


int main (int argc, char *argv[])
{
    int fd;
    char buf[256];
    //socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in addr, dst_addr;
    
    if((fd = socket(AF_INET, SOCK_STREAM, 0)) ==-1){
        client_exit(fd, "socket");
    }
    puts("socket init: OK!");

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8001);
    addr.sin_addr.s_addr = inet_addr("127.0.0.5");
    bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

    memset(&dst_addr, 0, sizeof(struct sockaddr_in));
    dst_addr.sin_family      = AF_INET;
    dst_addr.sin_port        = htons(8000);
    dst_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(fd, (struct sockaddr*)&dst_addr, sizeof(struct sockaddr_in)) == -1){
        client_exit(fd, "bind");
    }
    
    memset(buf, 0, 256);
    if(recv(fd, buf, 256, 0)==-1){
        client_exit(fd, "recv");
    }
    printf("server send >>  %s\n", buf);
    
    close(fd);
}
