#include <stdio.h>
#include <stdlib.h>
#include "modules/executor.h"



int main(int argc, char* argv[])
{
    char *path;
    char projname[256]={0};
    int fork_num = 0;

    if(parse(argc, argv, projname, &fork_num, NULL) == -1){
        puts("Please use:\n\t ./projtester -l|-L [num_proc] [proj_name]");
        exit(EXIT_FAILURE);
    }
    if(bincheck(projname, &path) == -1){
        exit(EXIT_FAILURE);
    }
    printf(" Process: (%s) \nLoop_num: (%d)\n\n", path, fork_num);

    if(task_manager(path, fork_num) == -1){
        exit(EXIT_FAILURE);
    }
}