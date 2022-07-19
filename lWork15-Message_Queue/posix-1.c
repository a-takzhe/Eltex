#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


#define handle_error(msg) \
        do { perror(msg); RESET; exit(EXIT_FAILURE); } while (0)

#define YELLOW        do { printf("\033[1;33m");} while (0)
#define RED           do { printf("\033[41m");} while (0)
#define RESET         do { printf("\033[0m");} while (0) 
#define STAT_MS(prt)  do { YELLOW; prt; RESET;} while (0)
#define ERROR_MS(prt) do { RED; prt; RESET;} while (0)  

#define MSG_SIZE 100
#define WQUEUE_NAME "/posix1"
#define RQUEUE_NAME "/posix2"

void set_attr(struct mq_attr* attr)
{
    attr->mq_maxmsg  = 10;
    attr->mq_msgsize = MSG_SIZE;
    attr->mq_curmsgs = 0;
    attr->mq_flags   = 0;
}

void send_mes(struct mq_attr attr, uint prior, const char *buffer)
{
    mqd_t mq_id;

    mq_id = mq_open(WQUEUE_NAME, O_WRONLY | O_CREAT, 0777, &attr);
    if(mq_id == -1){
        ERROR_MS(handle_error("mq_open write error"));
    }
    printf("Write Queue id: %d\n", mq_id);

    STAT_MS(puts("Sending a message..."));

    if(mq_send(mq_id, buffer, strlen(buffer), prior) == -1){
        ERROR_MS(handle_error("mq_send error"));   
    }
}

void recv_mes(struct mq_attr attr)
{
    mqd_t mq_id;
    uint prior;
    char buffer[MSG_SIZE];

    mq_id = mq_open(RQUEUE_NAME, O_RDONLY | O_CREAT, 0777, &attr);
    if(mq_id == -1){
        ERROR_MS(handle_error("mq_open read error"));
    }
    printf("Read Queue id: %d\n", mq_id);

    STAT_MS(puts("Waiting for a message from another process 'posix 2'..."));
    if(mq_receive(mq_id, buffer, sizeof(buffer), &prior) == -1)
    {
        ERROR_MS(handle_error("mq_receive error"));
    }
    printf("Message received: %s\n", buffer);

    mq_close(mq_id);
    if(mq_id == -1){
        ERROR_MS(handle_error("mq_unlink error"));
    }
    STAT_MS(puts("Close read queue!"));
}

int main (int argc, char* argv[])
{
    struct mq_attr attr;

    setvbuf(stdout, NULL, _IONBF, 0);
    STAT_MS(puts("Attr init"));
    set_attr(&attr);

    send_mes(attr, 1, "Hello from posix 1");
    STAT_MS(puts("start read"));
    recv_mes(attr);
    
    if(mq_unlink(WQUEUE_NAME) == -1){
        ERROR_MS(handle_error("mq_unlink error"));
    }
    puts("Queue is deleted!");

    STAT_MS(puts("Program is finished!\nPress enter to continue!"));
    while(getc(stdin)){
        break;
    }
    exit(0);
} 

// const char *vbuf_to_str(int a) {
//     switch (a) {
//     case _IONBF: return "_IONBF";
//     case _IOLBF: return "_IOLBF";
//     case _IOFBF: return "_IOFBF";
//     }
//     return "unknown";
// }

// int main() {
//     setvbuf(stderr, NULL, _IONBF, 0);
//     printf("%s\n", vbuf_to_str(getvbuf(stderr)));
//     setvbuf(stderr, NULL, _IOLBF, 0);
//     printf("%s\n", vbuf_to_str(getvbuf(stderr)));
//     setvbuf(stderr, NULL, _IOFBF, 0);
//     printf("%s\n", vbuf_to_str(getvbuf(stderr)));
// }

// #ifdef __GLIBC__
// #define _IO_UNBUFFERED        0x0002
// #define _IO_LINE_BUF          0x0200
// int getvbuf(FILE *f) {
//     if (f->_flags & _IO_UNBUFFERED) {
//         return _IONBF;
//     } else if (f->_flags & _IO_LINE_BUF) {
//         return _IOLBF;
//     }
//     return _IOFBF;
// }
// #else
// #error This program works only with glibc.
// #endif
