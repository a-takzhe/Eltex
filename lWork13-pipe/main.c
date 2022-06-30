#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define msg1 "Hello son!\n"
#define msg2 "What's up dad!\n"

void main(int argc, char* argv[])
{
    int pipefd1[2], //[0] - read
        pipefd2[2]; //[1] - write

    pid_t pid, wpid;
    const int BF_SIZE; 
    char BUFFER[BF_SIZE];
    pipe(pipefd1);
    pipe(pipefd2);

    pid = fork();
    if(pid != 0)
    {
        close(pipefd1[0]);
        close(pipefd2[1]);
        write(pipefd1[1], msg1, strlen(msg1));
        close(pipefd1[1]);
        wpid = wait4(pid, NULL, 0, NULL);
        if(wpid != pid) {
            perror("wait");
            exit(1);
        }
        read(pipefd2[0], BUFFER, BF_SIZE);
        printf("Child say: %s", BUFFER);
    }
    else
    {
        close(pipefd1[1]);
        close(pipefd2[0]);
        read(pipefd1[0], BUFFER, BF_SIZE);
        printf("Parent say: %s", BUFFER);
        close(pipefd1[0]);
        write(pipefd2[1], msg2, strlen(msg2));
        exit(0);
    }   
    exit(0);
}