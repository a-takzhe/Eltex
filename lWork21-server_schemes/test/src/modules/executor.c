#include "executor.h" 



// int start_proc(char *path, int fork_num)
// {
//     int status = 0;
//     struct rusage ru;
//     pid_t pid;
//     char *newargv[] = {path, NULL};
//     char *newenviron[] = { NULL };   

//     while (fork_num-- != 0)
//     {
//         pid = fork();
//         if(pid != 0)
//         {
//             wait4(pid, &status, 0, &ru);
//         }
//         else
//         {
//             execve(newargv[0], newargv, newenviron);
//             perror("execve");   /* execve() returns only on error */
//             return -1;
//         } 
//     }
       
//     return 0;
// }

static void* start_proc(void* arg)
{
    char* path = (char*)arg;
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
        execve(newargv[0], newargv, newenviron);
        perror("execve");   /* execve() returns only on error */
    } 
    return NULL;
}

int task_manager(char *path, int fork_num)
{
    pthread_t *id_threads;
    pthread_attr_t attr;

    id_threads = calloc(fork_num, sizeof(pthread_t));
    pthread_attr_init(&attr);
    
    while(fork_num-- != 0)
    {
        pthread_create(&id_threads[fork_num], &attr, start_proc, path);
    }

    while(fork_num-- != 0)
    {
        pthread_join(id_threads[fork_num], NULL);
    } 

    free(id_threads);
    return 0;
}