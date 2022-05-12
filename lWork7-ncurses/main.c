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

int change_x(point *p, short v);
int change_y(point *p, short v);

int main(int argc, char ** argv)
{
    init_menu(&__MENU__);
    init(__MAINWND__, __TOOLSWND__, __HTOOLWND__, __MENU__);
    
    if(argc >= 2)
    {
        read_file(argv[1], __MAINWND__);
    }
    else
    {
        wmove(__MAINWND__,0,0);
        wrefresh(__MAINWND__);
    }

    WINDOW* use_wnd = __MAINWND__;
    noecho();
    keypad(use_wnd, true);
    int key;
    point p = {.x = use_wnd->_curx, 
               .y = use_wnd->_cury};

    while (key = wgetch(use_wnd))
    {
        if(key == KEY_F(3) || key == '\n') break;
        MENU* a = get_menu_by_key(key, __MENU__);
        
        if(a != NULL && a->isUseSubstr)
        {
            fill_toolbar(a->subMenu);

            use_wnd = __MAINWND__;
            wmove(__HTOOLWND__, 0, 0);
            wrefresh(__HTOOLWND__);  
        }
        switch (key)
        {
            case KEY_DOWN:
                change_y(&p, +1);
                break;
            case KEY_UP:
                change_y(&p, -1);
                break;
            case KEY_LEFT:
                change_x(&p, -1);
                break;
            case KEY_RIGHT:
                change_x(&p, +1);
                break;
            case KEY_BACKSPACE:
                wmove(use_wnd, p.y, --p.x);
                wprintw(use_wnd," ");
                break;
            default:
                wprintw(use_wnd, "%c", key);
                p.x++;            
                break;
        }

        wmove(use_wnd, p.y, p.x);
        wrefresh(use_wnd);

    }
    // getch();

   
    wend();
    exit(EXIT_SUCCESS);
}

int change_x(point *p, short v)
{
    if(v<0)
    {
        if(p->x>0)
        {
            p->x--;
        } 
        else
        {
            if(change_y(p, -1) != ERR)
            {
                p->x=__MAINWND__->_maxx;
            }
            else return -1;
        }
    }
    else if(v>0)
    {
        if(p->x<__MAINWND__->_maxx)
        {
            p->x++;
        }
        else
        {
            if(change_y(p, +1) != ERR)
            {
                p->x = 0;
            }
            else return -1;
        }
    }
    return 1;
}

int change_y(point *p, short v)
{
    if(v<0)
    {
        if(p->y > 0) p->y--;
        else return -1;
    }
    else if(v>0)
    {
        if(p->y < __MAINWND__->_maxy) p->y++;
        else return-1;
    }
    return 1;
}