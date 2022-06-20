#include "strok.h"

int isExit(char* str)
{
    return (strcmp(str, "exit") == 0 || strstr(str, "exit") != NULL);
}

int get_nparam(char* str)
{
    char* saveptr;
    char* res;
    int i = 0;

    while((res = strtok_r(str, " ", &saveptr))!=NULL)
    {
        printf("\tstr: |%s| saveptr: |%s|\n", res, saveptr);
        i++;
        str = NULL;
    } 
    return i;
}