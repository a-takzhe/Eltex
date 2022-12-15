#include "executor.h" 

int start_proc(char *path, int fork_num)
{
    int status = 0;
    struct rusage ru;
    pid_t pid;
    char *newargv[] = {path, NULL};
    char *newenviron[] = { NULL };   

    pid = fork();
    if(pid != 0)
    {
        wait4(pid, &status, 0, &ru);
    }
    else
    {
        printf("run proc: %s\n", newargv[0]);
        execve(newargv[0], newargv, newenviron);
        perror("execve");   /* execve() returns only on error */
        return -1;
    }

    if(WIFEXITED(status) != 0)
        return WEXITSTATUS(status);
    else
        return 0;
}