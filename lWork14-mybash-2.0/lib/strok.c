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
    char* saveptr;
    char* res;
    int i = 0;

    strcpy(tmpstr, str);
    while((res = strtok_r(tmpstr, " ", &saveptr))!=NULL)
    {
        i++;
        if(tmpstr != NULL){
            free(tmpstr);
            tmpstr = NULL;
        }
        tmpstr = NULL;
    } 
    return i;
}

int fillargv(char** argv, char* str)
{
    char* tmpstr = (char*)calloc(strlen(str), sizeof(char));
    char* saveptr, *forfree;
    char* res;
    int i = 0;

    strcpy(tmpstr, str);
    forfree = tmpstr;
    while((res = strtok_r(tmpstr, " ", &saveptr))!=NULL)
    {
        argv[i] = (char*)malloc(strlen(res)+1*sizeof(char));
        strcpy(argv[i], res);
        tmpstr = NULL;
        i++;
    } 
    argv[i] = NULL;
    free(forfree);
    return 1;
}

int get_nfunc(char* str)
{
    int f=0;
    for (size_t i = 0; i < strlen(str); i++){
        if(*(str+i) == '|') f++;
    }
    return f+1;    
}