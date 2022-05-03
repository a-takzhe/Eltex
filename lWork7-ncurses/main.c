#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include "bin/compare.h"

#define TYPE_CALLOC(type,elts) typeCalloc(type, (unsigned)(elts))

WINDOW *__MAINWND__;
WINDOW *__HTOOLWND__;
WINDOW *__TOOLSWND__;
MENU *__MENU__;

int main(int argc, char ** argv)
{
    init_menu(&__MENU__);
    init();
    getch();
    wclear(__TOOLSWND__);
    wrefresh(__TOOLSWND__);
    getch();
    fill_tools(__MENU__);
    wrefresh(__TOOLSWND__);
    getch();
    wend();

    // puts("\nmenu show:");
    // show_menu(__MENU__, 0);
    
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

   

    

    //end_compare();
    exit(EXIT_SUCCESS);
}