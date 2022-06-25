#include "execve.h"

int exec(char* str)
{
    int nparam = 0;
    int status = 0;
    struct rusage ru;
    pid_t PID, wpid;
    char **newargv;
    char *newenviron[] = { NULL };                      

    if((nparam = get_nparam(str)) == 0) return 1;

    newargv = (char**)malloc((nparam+2)*sizeof(char*));
    fillargv(newargv, str);
    
    PID = fork();
    if(PID != 0)
    {
        wpid = wait4(PID, &status, 0, &ru);
    }
    else
    {
        execvp(newargv[0], newargv);
        perror("execve");   /* execve() returns only on error */
        exit(EXIT_FAILURE);
    }

    printf("WIFEXITED  : %d\n", WIFEXITED  (status));    
    printf("WEXITSTATUS: %d\n", WEXITSTATUS(status));    
    printf("WIFSIGNALED: %d\n", WIFSIGNALED(status));    
    printf("WTERMSIG   : %d\n", WTERMSIG   (status));    
    printf("WIFSTOPPED : %d\n", WIFSTOPPED (status));    
    printf("WSTOPSIG   : %d\n", WSTOPSIG   (status));    

    //free memory
    for (size_t i = 0; i < nparam+2; i++)
    {
        free(newargv[i]);
    }
    free(newargv);
    
}