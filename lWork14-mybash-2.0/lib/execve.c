#include "execve.h"

int ran_proc(char* str);

void initdesc()
{
    mystdout = dup(fileno(stdout));
    mystdin = dup(fileno(stdin));
}

static void deftopipe(int* pipefd)
{
    if(dup2(pipefd[1], fileno(stdout)) == -1){
        handle_error("dup2");
    }
    if(dup2(pipefd[0], fileno(stdin)) == -1){
        handle_error("dup2");
    }
}

static void setdefault()
{
    dup2(mystdout, fileno(stdout));
    dup2(mystdin, fileno(stdin));
}

///////////////////////////
// stdout -> pipefd1[1] //
// stdin  -> pipefd1[0] //
//////////////////////////

int exec(char* str)
{
    char* saveptr, *res;
    int __fl = 0;
    int ch = 1;
    int pipefd[2];

    if(strcmp(str, "|") != 0){
        pipe(pipefd);
        deftopipe(pipefd);
    }

    while((res=strtok_r(str, "|", &saveptr)) != NULL)
    {       
        setdefault();
        printf("comm: %s\n", res);
        if(ch == 1){
            if(dup2(pipefd[1], fileno(stdout)) == -1){
                handle_error("dup2");
            }
        }
        if(ch == 2){
            close(pipefd[1]);
            if(dup2(pipefd[0], fileno(stdin)) == -1){
                handle_error("dup2");
            }
        }

        if((__fl = ran_proc(res)) != 0){
            puts("empty com");
            break;
        }
        
        ch++;
        if(ch > 2){
            __fl = -5;
            break;
        }
        str = NULL;
    }
    setdefault();
    if(__fl != 0){
        printf("__fl: %d\n", __fl);
    }

    return 0;

}

int ran_proc(char* str)
{
    int nparam = 0;
    int status = 0;
    struct rusage ru;
    pid_t pid, wpid;
    char **newargv;
    char *newenviron[] = { NULL };                      

    if((nparam = get_nparam(str)) == 0){
        return 1;
    }

    newargv = (char**)malloc((nparam+2)*sizeof(char*));
    fillargv(newargv, str);
    
    pid = fork();
    if(pid != 0)
    {
        wpid = wait4(pid, &status, 0, &ru);
    }
    else
    {
        execvp(newargv[0], newargv);
        perror("execve");   /* execve() returns only on error */
        exit(EXIT_FAILURE);
    }

    //free memory
    for (size_t i = 0; i < nparam+2; i++)
    {
        free(newargv[i]);
    }
    free(newargv);

    return WEXITSTATUS(status);
}