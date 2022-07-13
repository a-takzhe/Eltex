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
        puts("write file name: ./systemV-1 ./[file]");
        exit(EXIT_FAILURE);
    }

    key = ftok(argv[1], PROJ_ID);
    if(key == -1 ){
        handle_error("ftok error");
    }
    printf("generating key: %d...\n", key);
    
    q_id = msgget(key, 0);
    if(q_id == -1){
        handle_error("msgget error");
    }
    printf("queue id: %d...\n", q_id);

    msgctl(q_id, IPC_STAT, &q_data);
    printf("msg_qnum: %ld, msg_qbytes: %ld\n", q_data.msg_qnum, q_data.msg_qbytes);

    if (msgrcv(q_id, (void *) &buff, sizeof(buff.message), 1, MSG_NOERROR) == -1) 
    {
        if (errno != ENOMSG) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("No message available for msgrcv()\n");
    } 
    else
        printf("message received: %s\n", buff.message);



    buff.mtype = 2;
    strcpy(buff.message, "Hello from systemV-2");
    if(msgsnd(q_id, (void*) &buff, sizeof(buff.message), IPC_NOWAIT) == -1){
        handle_error("msgsnd error");
    }
    puts("send message to queue...");
    while(getc(stdin)){
        exit(0);
    }

    exit(0);
}