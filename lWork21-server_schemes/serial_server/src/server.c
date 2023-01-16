#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>

#define serv_exit(fd, func_name) \
        do{perror(func_name); close(fd); exit(EXIT_FAILURE);}while(0)

void currentTime(char * const buf)
{
    time_t timep = time(NULL);
    struct tm* ltime = localtime(&timep);
    if (ltime == NULL) {
        perror("localtime");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0, 256);

    if(strftime(buf, 256, "%d-%m-%Y %H:%M:%S", ltime) == 0){
        perror("strftime");
        exit(EXIT_FAILURE);
    };
}

int main (int argc, char *argv[])
{
    int fd, dst_fd;
    char buf[256];
    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in addr, dst_addr;
    

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) ==-1){
        serv_exit(fd, "socket");
    }
    puts("socket init: OK!");

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(fd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) == -1){
        serv_exit(fd, "bind");
    }
    puts("socket bind: OK!");
    
    if(listen(fd, 5) == -1){
        serv_exit(fd, "listen");
    }
    puts("server is waiting for a connection...");

    while(1)
    {    
        memset(&dst_addr, 0, sizeof(struct sockaddr_in));
        if((dst_fd = accept(fd, (struct sockaddr*)&dst_addr, &len)) == -1){
            serv_exit(fd, "accept");
        }

        if(getpeername(dst_fd, (struct sockaddr*)&dst_addr, &len) == -1){
            serv_exit(fd, "getsockname");
        }
        printf("client <%s:%d> accepted!\n", inet_ntoa(dst_addr.sin_addr), ntohs(dst_addr.sin_port));
        
        currentTime(buf);
        if(send(dst_fd, buf, sizeof(buf), 0) == -1){
            serv_exit(fd, "send");
        }

        close(dst_fd);
    }
}