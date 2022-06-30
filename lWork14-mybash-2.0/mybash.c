#include <stdio.h>
#include <termios.h>
#include "lib/execve.h"

int main(int argc, char** argv)
{
    char* str = NULL;
    size_t len;
    ssize_t s_len;
    short syn_fl = 0;

    while (1)
    {
        printf("\033[1m");//bold
        printf("\033[1;36m");//cyan
        printf("%s", argv[0]);
        printf("\033[1;33m");//yellow
        printf("~print command >> ");
        printf("\033[0m");//reset
        
        if((s_len=getline(&str, &len, stdin)) == -1)
        {
            perror("getline");
            free(str);
            exit(EXIT_FAILURE);
        }

        if(uEscape(str)) 
        {
            puts("can't use escape sequence");
            continue;
        }            
        if(isExit(str)) break;
        str[s_len-1]=0;
        
        exec(str);
    }
    
    free(str);
    exit(EXIT_SUCCESS);    
}


//     struct termios old_term, new_term;
//     char c;

//   /* Get old terminal settings for further restoration */
//   tcgetattr(fileno(stdin), &old_term);

//   /* Copy the settings to the new value */
//   new_term = old_term;

//   /* Disable echo of the character and line buffering */
//   new_term.c_lflag &= (~ICANON & ~ECHO);
//   /* Set new settings to the terminal */
//   tcsetattr(fileno(stdin), TCSANOW, &new_term);

//   while ((c = getchar()) != 'q') {
//     if(c==27)
//     {
//         syn_fl = 3;
//     }
//     if(syn_fl!=0)
//     {
//         syn_fl--;
//         continue;
//     }
//     printf("You pressed: %c\n", c);
//   }


//   /* Restore old settings */
//   tcsetattr(fileno(stdin), TCSANOW, &old_term);
