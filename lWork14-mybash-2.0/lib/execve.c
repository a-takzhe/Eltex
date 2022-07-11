#include "execve.h"

int ran_proc(char* str);
void pipeclear(int infd);

void initdesc()
{
    mystdout = dup(fileno(stdout));
    mystdin = dup(fileno(stdin));
}

static void deftopipe(int* pipefd)
{
    if(dup2(pipefd[1], fileno(stdout)) == -1){
        handle_error("dup2 stdout");
    }
    if(dup2(pipefd[0], fileno(stdin)) == -1){
        handle_error("dup2 stdin");
    }
}

static void setdefault()
{
    dup2(mystdout, fileno(stdout));
    dup2(mystdin, fileno(stdin));
}

void pipeclear(int infd)
{
    int i=0;
    while(read(infd, GLOB_BUFF, BUFSIZE) > 0){
        if(i==0){
            printf("\e[41m  Trash from pipe:\e[0m\n\e[0;33m");
        }   
        printf("%s ", GLOB_BUFF);
        i++;
    }
    puts("\e[0m");
}
///////////////////////////
// stdout -> pipefd1[1] //
// stdin  -> pipefd1[0] //
//////////////////////////

int exec(char* str)
{
    char* saveptr, *res; 
    int out_fl = 0;
    int ch = 0;

    int pipefd[2];
    char debug[100];
    int fnum = get_nfunc(str);

    if(fnum > 1){
        pipe(pipefd);
        deftopipe(pipefd);
        out_fl = -1;
    }

    while((res=strtok_r(str, "|", &saveptr)) != NULL)
    {       
        snprintf(debug, 90, "\e[1;35mcommand: %s\e[0m\n", res);
        write(mystdout, debug, strlen(debug));
        
        if(ch+1 == fnum && fnum > 1){
            dup2(mystdout, fileno(stdout));
            close(pipefd[1]);
            out_fl = 0;
        }

        if(ran_proc(res) != 0){
            write(mystdout, "\e[41merror command!\e[0m\n", 24);
            out_fl = -1;
            break;
        }
        ch++;   
        str = NULL;
    }

    if(out_fl != 0 && fnum > 1){
        dup2(mystdout, fileno(stdout));
        close(pipefd[1]);
        pipeclear(pipefd[0]);
    }
    if(fnum > 1){
        dup2(mystdin, fileno(stdin));
        close(pipefd[0]);
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

    if(WIFEXITED(status) != 0)
        return WEXITSTATUS(status);
    else
        return 0;
}