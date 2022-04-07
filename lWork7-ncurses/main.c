#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include "bin/compare.h"

#define TYPE_CALLOC(type,elts) typeCalloc(type, (unsigned)(elts))

struct command{
    char* key;
    char* description;
};



int main(int argc, char ** argv)
{
    // init_compare(argc, argv);
    
    FILE* f;
    char buf[20] = {0};

    if((f = fopen("./configure/cmd.config", "r")) == NULL)
    {
        puts("file note open");
        return -1;
    }
    char *key_dsc;
    char *strptr;
    char key_ch[20];
    //const char *s = "F1;open;file";
    while ((fgets(buf, 20, f)))
    {
        &(key_ch[0]) = strtok(buf, ";");
        //key_dsc = strtok(NULL,"");
        //printf("fread symbols: %s", cnt);
        printf("\tch_key: %s\n", key_ch);
        //printf("\tkey_dsc: %s\n", key_dsc);
        printf("buf: %s\n", buf);
    }
    

    fclose(f);
        
    // int key;
    // int i=1;
    // wmove(cmdinpwnd,0,0);
    // keypad(cmdinpwnd, TRUE);
    // wbkgd(cmdinpwnd, COLOR_PAIR(CMDWND_COLOR) | A_REVERSE);
    // wrefresh(cmdinpwnd);
    // while (key = wgetch(cmdinpwnd))
    // {
    //     if(key == KEY_F(3) || key == '\n') break;
    //     //wmove(cmdinpwnd, 0, i);
    //     //wechochar(cmdinpwnd, key);
    //     // wprintw(cmdinpwnd,"");
    //     i++;
    // }


    // end_compare();
    exit(EXIT_SUCCESS);
}