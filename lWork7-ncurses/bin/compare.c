#include "compare.h"

//-------------------
//prototype function
//-------------------
int write_t(WINDOW *wnd, char *key, char *func, point *pos);
void init_color_pairs();
void sig_winch(int signo);
int init_w();


//-------------------------
//function implementation
//-------------------------
void init_color_pairs()
{
    start_color();
    init_color(TEXT_COLOR, 754, 669, 535);
    init_color(MAIN_BACK_COLOR, 100, 100, 100);
    init_color(CONTROL_BACK_COLOR, 400, 400, 400);
    
    init_pair(MAINWND_COLOR, TEXT_COLOR, MAIN_BACK_COLOR);
    init_pair(TOOLSWND_COLOR, COLOR_WHITE, CONTROL_BACK_COLOR);
}

int rewrite_mwnd(int r)
{
    wmove(__MAINWND__, 0, 0);
    wclear(__MAINWND__);
    while(NOTE[r][0] != 0 && r < __MAINWND__->_maxy)
    {
        wprintw(__MAINWND__, "%s", NOTE[r]);
        r++;
    }
}

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    refresh();

    if(wgetch(stdscr) == KEY_RESIZE)
    {
        wresize(__MAINWND__, size.ws_row-2, size.ws_col);
        rewrite_mwnd(0);

        wresize(__HTOOLWND__, 1, size.ws_col);
        mvwin(__HTOOLWND__, size.ws_row-2, 0);
        
        wresize(__TOOLSWND__, 1, size.ws_col);
        mvwin(__TOOLSWND__, size.ws_row-1, 0);

        if(wdelta - size.ws_col <= -5)
        {
            fill_toolbar(CURMEN);
            wdelta = size.ws_col;
        }     
        else if(wdelta - size.ws_col >= 0){
            wdelta = size.ws_col;
        }  
    }
    wrefresh(__HTOOLWND__);
    wrefresh(__TOOLSWND__);
    wrefresh(__MAINWND__);
}

int init()
{
    if(stdscr != NULL || __MAINWND__ != NULL) 
    { 
        wend();
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    init_color_pairs();
    signal(SIGWINCH, sig_winch);
    refresh();
    
    if(init_w() == ERR) return ERR;
    if(init_menu(&__MENU__) == ERR) return ERR;
    if(fill_toolbar(__MENU__) == ERR) return ERR;

    wmove(__MAINWND__, 0,0);
    wrefresh(__MAINWND__);

    return 0;
}

int init_w()
{
    struct winsize size;
    u_short res = 0;

    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    
    __MAINWND__ = newwin(size.ws_row-2, size.ws_col, 0, 0);
    keypad(__MAINWND__, true);
    res = wbkgd(__MAINWND__, COLOR_PAIR(MAINWND_COLOR));
    
    __HTOOLWND__ = newwin(1, size.ws_col, size.ws_row - 2, 0);
    keypad(__HTOOLWND__, true);
    res = wbkgd(__HTOOLWND__, __MAINWND__->_bkgd | A_REVERSE);

    __TOOLSWND__ = newwin(1, size.ws_col, size.ws_row-1, 0);
    res = wbkgd(__TOOLSWND__, COLOR_PAIR(TOOLSWND_COLOR));
    wdelta = size.ws_col;

    res = wrefresh(__MAINWND__);
    res = wrefresh(__HTOOLWND__);
    res = wrefresh(__TOOLSWND__);

    return res;
}

int fill_toolbar(MENU* menu)
{
    point pos = {.x=0, .y=0};
    wclear(__TOOLSWND__);
    CURMEN = menu;

    while (menu != NULL)
    {
        if(pos.x+strlen(menu->key_name)+strlen(menu->func) > __TOOLSWND__->_maxx) {
            break;
        }
        write_t(__TOOLSWND__, menu->key_name, menu->func, &pos);
        pos.x+=3;
        menu = menu->nextFunc;
    }
    return 0;
}

int write_t(WINDOW *wnd, char *key_name, char *func, point *pos)
{
    WINDOW *ckw, *dkw;

    ckw = derwin(wnd, 1, strlen(key_name), pos->y, pos->x);

    wmove(ckw, 0,0);
    wbkgd(ckw, wnd->_bkgd | A_REVERSE);
    wprintw(ckw, key_name);
    wrefresh(ckw);
    pos->x += strlen(key_name);
    
    wmove(wnd, pos->y, pos->x);
    wprintw(wnd,":%s", func);
    pos->x += strlen(func);
    wrefresh(wnd);
} 

int wend()
{
    delwin(__MAINWND__);
    delwin(__HTOOLWND__);
    delwin(__TOOLSWND__);
    endwin();
}
