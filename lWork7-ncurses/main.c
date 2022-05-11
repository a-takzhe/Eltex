#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h>
#include "bin/compare.h"
#include "bin/read_from_file.h"


WINDOW *__MAINWND__;
WINDOW *__HTOOLWND__;
WINDOW *__TOOLSWND__;
MENU *__MENU__;

int main(int argc, char ** argv)
{
    init_menu(&__MENU__);
    init(__MAINWND__, __TOOLSWND__, __HTOOLWND__, __MENU__);
    
    if(argc >= 2)
    {
        read_file(argv[1], __MAINWND__);
    }

    // WINDOW* use_wnd = __MAINWND__;
    // int key;
    // int i=1;
    // wmove(__MAINWND__,0,0);
    // keypad(__MAINWND__, TRUE);
    // wrefresh(__MAINWND__);

    // while (key = wgetch(use_wnd))
    // {
    //     if(key == KEY_F(3) || key == '\n') break;
    //     MENU* a = get_menu_by_key(key, __MENU__);
        
    //     if(a != NULL && a->isUseSubstr)
    //     {
    //         fill_toolbar(a->subMenu);

    //         use_wnd = __MAINWND__;
    //         wmove(__HTOOLWND__, 0, 0);
    //         wrefresh(__HTOOLWND__);  
    //     }
    // }
    getch();

   
    wend();
    exit(EXIT_SUCCESS);
}