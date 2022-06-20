#include <stdio.h>
#include "lib/execve.h"
#include "lib/strok.h"

int main(int argc, char** argv)
{
    char* str = NULL;
    char* str1 = NULL;
    size_t* len;

    while (1)
    {
        printf("\033[1m");//bold
        printf("\033[1;36m");//cyan
        printf("%s", argv[0]);
        printf("\033[1;33m");//yellow
        printf("~print command >> ");
        printf("\033[0m");//reset
        
        if(getline(&str1, len, stdin) == -1)
        {
            perror("getline my");
            exit(EXIT_FAILURE);
        }

        if(isExit(str1)) break;

        // str[strlen(str)-1]=0;

        // printf("0>%c<\n", str[0]);
        // printf("1>%c<\n", str[1]);
        // printf("S>%s<\n", str);
        // printf("L>%s<\n", str+5);
        // char* c = (str + 5);
        // c = '\0';

        // exec(&str);
        // free(str);        
    }
    
    free(str1);
    exit(EXIT_SUCCESS);    
}