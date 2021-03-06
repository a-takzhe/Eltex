#include "strok.h"

int isExit(char* str)
{
    return (strcmp(str, "exit") == 0 || strstr(str, "exit") != NULL);
}

int uEscape(char* str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if(str[i]==27 || str[i]==1) return 1;
    }
    return 0;
}

int get_nparam(char* str)
{
    char* tmpstr = (char*)calloc(strlen(str), sizeof(char));
    char* saveptr, *fptr;
    char* res;
    int i = 0;

    strcpy(tmpstr, str);
    fptr = tmpstr;
    while((res = strtok_r(tmpstr, " ", &saveptr))!=NULL)
    {
        i++;
        tmpstr = NULL;
    } 
    free(fptr);
    return i;
}

int fillargv(char** argv, char* str)
{
    char* tmpstr = (char*)calloc(strlen(str), sizeof(char));
    char* saveptr, *fptr;
    char* res;
    int i = 0;

    strcpy(tmpstr, str);
    fptr = tmpstr;
    while((res = strtok_r(tmpstr, " ", &saveptr))!=NULL)
    {
        argv[i] = (char*)malloc(strlen(res)+1*sizeof(char));
        strcpy(argv[i], res);
        tmpstr = NULL;
        i++;
    } 
    argv[i] = NULL;

    free(fptr);
    return 1;
}