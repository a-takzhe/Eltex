#include <stdio.h>
#include <termios.h>
#include "lib/execve.h"


int main(int argc, char** argv)
{
    char* str = NULL;
    size_t len;
    ssize_t s_len;
    short syn_fl = 0;
    
    initdesc();
    while (1)
    {
        printf("\033[1m");            //bold
        printf("\033[1;36m");         //cyan
        printf("%s", argv[0]);
        printf("\033[1;33m");         //yellow
        printf("~print command >> ");
        printf("\033[0m");            //reset
        
        s_len = getline(&str, &len, stdin); 

        if(s_len == -1){
            free(str);
            handle_error("getline");
        }
        if(uEscape(str)){
            puts("don't use escape sequences");
            continue;
        }   
        if(isExit(str)){
            break;
        }
        str[s_len-1] = 0;

        exec(str);
    }
    
    free(str);
    exit(0);
}