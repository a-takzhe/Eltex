#include <stdio.h>
#include <stdlib.h>
#include "modules/parser.h"



int main(int argc, char* argv[])
{
    char appName[256]={0};
    int fork_num = 0;

    if(parse(argc, argv, appName, &fork_num, NULL) == -1){
        puts("please use all param!");
        exit(EXIT_FAILURE);
    }
    
    if(bincheck(appName) == -1){
        exit(EXIT_FAILURE);
    }

    printf("proc: (%s) loop_num: (%d)\n", appName, fork_num);

}