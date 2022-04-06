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
    init_compare(argc, argv);
   
    // box(mainwnd, '.', '.');
    // box(cmdwnd, '.', '.');
    
    // wbkgd(mainwnd, COLOR_PAIR(1) | A_BOLD);
    
    //getch();
    
    int key;
    int i=1;
    wmove(cmdinpwnd,0,0);
    keypad(cmdinpwnd, TRUE);
    while (key = wgetch(cmdinpwnd))
    {
        if(key == KEY_F(3)) break;
        //wmove(cmdinpwnd, 0, i);
        //wechochar(cmdinpwnd, key);
        // wprintw(cmdinpwnd,"");
        i++;
    }
    
    // wmove(mainwnd, 1, 1);
    // //wrefresh(mainwnd);
    // getch();

    // wmove(cmdwnd, 1, 1);
    // wrefresh(cmdwnd);
    // getch();
    // wnd = newwin(3, size.ws_col, size.ws_row-3, 0);
    // box(wnd, '|', '-');
    // //subwnd = derwin(wnd, 4, 16, 1, 1);
    // // wprintw(subwnd, "Hello, brave new curses world!\n");
    // wmove(wnd, 1,1);

    // wprintw(wnd, "F1 - open file");
    // wrefresh(wnd);
    // //delwin(subwnd);
    // delwin(wnd);
    // wattroff(wnd, COLOR_PAIR(1)|A_BOLD);


    end_compare();
    exit(EXIT_SUCCESS);
}