#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
    pid_t PID = fork();

    if(PID != 0)
    {
        printf("parent pid: %d\n", getpid());
        printf("parent ppid: %d\n", getppid());
        //printf("my children pid: %d\n", PID);
        // waitpid(PID, WAIT_ANY, NULL);
        wait(NULL);
    }
    else
    {
        printf("children pid: %d\n", getpid());
        printf("children ppid: %d\n", getppid());
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}