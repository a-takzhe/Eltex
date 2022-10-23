#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void simple_action(int signum)
{
    printf("Oh, sheat!\nThis is disposition of signal=(%d)!\n", signum);
    exit(EXIT_SUCCESS);
}

void action(int signum, siginfo_t* info, void* context)
{
    printf("Oh, sheat!\nThis is disposition of signal=(%d)!"
            " form user uid=(%d) and pid=(%d)\n", signum, info->si_uid, info->si_pid);
}



int main (void)
{
    struct sigaction act1, old_act1;
    struct sigaction act2, old_act2;

    act1.sa_handler = &simple_action;
    act1.sa_mask.__val[SIGINT] = 1;


    if(sigaction(SIGTERM, &act1, &old_act1) == -1)
    {
        printf("ops!\n");
        exit(EXIT_FAILURE);
    }

    act2.sa_sigaction = &action;
    act2.sa_flags = SA_SIGINFO;
    if(sigaction(SIGQUIT, &act2, &old_act2) == -1)
    {
        printf("ops!\n");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        puts("do something ...");
        sleep(5);
    }
}

