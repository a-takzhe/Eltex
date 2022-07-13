#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/stat.h>

#define YELLOW do { printf("\033[1;33m");} while (0)
#define RED    do { printf("\e[41m");} while (0)
#define RESET  do { printf("\033[0m");} while (0) 
#define STAT_MS(prt) do { YELLOW; prt; RESET;} while (0)
#define ERROR_MS(prt) do { RED; prt; RESET;} while (0)  


#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct _msgbuf
{
    long mtype;
    char message[100];
} typedef msgbuf;

int PROJ_ID = 0;

int main (int argc, char* argv[])
{
    int q_id;
    key_t key;
    struct msqid_ds q_data;
    msgbuf buff;    

    if(argc < 2){
        ERROR_MS(puts("write file name: ./systemV-1 ./[file]"));
        exit(EXIT_FAILURE);
    }

    STAT_MS(puts("Start program V-1..."));
    
    //generate token
    key = ftok(argv[1], PROJ_ID);
    if(key == -1 ){
        ERROR_MS(handle_error("ftok error"));
    }
    printf("Generated key: %d\n", key);
    
    //Get message queue ID
    q_id = msgget(key, IPC_CREAT | 0777);
    if(q_id == -1){
        ERROR_MS(handle_error("msgget error"));
    }
    printf("Queue id:      %d\n", q_id);
    
    //get queue configuration
    msgctl(q_id, IPC_STAT, &q_data);
    printf("msg_qnum: %ld, msg_qbytes: %ld\n", q_data.msg_qnum, q_data.msg_qbytes);


    STAT_MS(puts("Sending a message..."));
    buff.mtype = 1;
    strcpy(buff.message, "Hello from systemV-1");

    if(msgsnd(q_id, (void*) &buff, sizeof(buff.message), IPC_NOWAIT) == -1){
        handle_error("msgsnd error");
    }
    puts("Message sent!");

    STAT_MS(puts("Waiting for a message with prior(2) from another process..."));
    if (msgrcv(q_id, (void *) &buff, sizeof(buff.message), 2, MSG_NOERROR) == -1) 
    {
        if (errno != ENOMSG) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("No message available for msgrcv()\n");
    } 
    else printf("Message received: %s\n", buff.message);


    
    // buff2.message[0] = 0;
    // if (msgrcv(q_id, (void *) &buff2, sizeof(buff2.message), 1, MSG_NOERROR | IPC_NOWAIT) == -1) 
    // {
    //     if (errno != ENOMSG) {
    //         perror("msgrcv");
    //         exit(EXIT_FAILURE);
    //     }
    //     printf("No message available for msgrcv()\n");
    // } 
    // else
    //     printf("message received: %s\n", buff2.message);
    
    STAT_MS(puts("Program is finished!\nPress any key to continue!"));
    while(getc(stdin)){
        exit(0);
    }
    exit(0);
}