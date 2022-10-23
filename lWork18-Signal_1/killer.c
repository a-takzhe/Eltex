#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char buf[512], buf1[512];
    int sig;

    FILE *cmd_pipe = popen("pidof -s some_proc", "r");
    FILE *cmd_pipe1 = popen("pidof -s killer", "r"); 

    fgets(buf, 512, cmd_pipe);
    fgets(buf1, 512, cmd_pipe1);

    printf("some_proc pid: %s", buf);
    printf("killer pid: %s", buf1);

    
    pid_t pid = strtoul(buf, NULL, 10);
    
    pclose(cmd_pipe); 
    pclose(cmd_pipe1);

    printf("sig = %s\n", argv[1]);
    sig = strtol(argv[1], NULL, 10);
    printf("kill %d %d\n",sig, pid);

    kill(pid, sig);
}