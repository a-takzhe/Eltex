#include <stdio.h>
#include <stdlib.h>
#include "modules/parser.h"



int main(int argc, char* argv[])
{
    char appName[256];
    int fork_num;

    if(parse(argc, argv, appName, &fork_num, NULL) == -1){
        puts("please use all param!");
        exit(EXIT_FAILURE);
    }
    
    printf("argc: %d\n", argc);
}