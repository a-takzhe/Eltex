#include "compare.h"

void init_color_pairs()
{
    start_color();
    init_color(TEXT_COLOR, 754, 669, 535);
    init_color(MAIN_BACK_COLOR, 100, 100, 100);
    init_color(CONTROL_BACK_COLOR, 400, 400, 400);
    
    init_pair(MAINWND_COLOR, TEXT_COLOR, MAIN_BACK_COLOR);
    init_pair(TOOLSWND_COLOR, COLOR_WHITE, CONTROL_BACK_COLOR);
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
       
        wresize(__HTOOLWND__, 1, size.ws_col);
        mvwin(__HTOOLWND__, size.ws_row-2, 0);
        
        wresize(__TOOLSWND__, 1, size.ws_col);
        mvwin(__TOOLSWND__, size.ws_row-1, 0);

        wclear(__MAINWND__);
        if(wdelta - size.ws_col <= -5)
        {
            fill_tools(CMENU);
            wdelta = size.ws_col;
        }     
        else if(wdelta - size.ws_col >= 0){
            wdelta = size.ws_col;
        }  
    }
    wrefresh(__HTOOLWND__);
    wrefresh(__TOOLSWND__);
    wrefresh(__MAINWND__);
    refresh();
}

int init()
{
    if(stdscr != NULL || __MAINWND__ != NULL) wend();

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    init_color_pairs();
    signal(SIGWINCH, sig_winch);
    refresh();
    
    if(init_w() == ERR) return -1;
    CMENU = __MENU__;
    if(fill_tools(__MENU__) == ERR) return -1;

    return 0;
}

int init_w()
{
    struct winsize size;
    u_short res = 0;

    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    
    __MAINWND__ = newwin(size.ws_row-2, size.ws_col, 0, 0);
    res = wbkgd(__MAINWND__, COLOR_PAIR(MAINWND_COLOR));
    
    __HTOOLWND__ = newwin(1, size.ws_col, size.ws_row - 2, 0);
    res = wbkgd(__HTOOLWND__, __MAINWND__->_bkgd | A_REVERSE);

    __TOOLSWND__ = newwin(1, size.ws_col, size.ws_row-1, 0);
    res = wbkgd(__TOOLSWND__, COLOR_PAIR(TOOLSWND_COLOR));
    wdelta = size.ws_col;

    res = wrefresh(__MAINWND__);
    res = wrefresh(__HTOOLWND__);
    res = wrefresh(__TOOLSWND__);

    return res;
}

int fill_tools(MENU* menu)
{
    point pos = {.x=0, .y=0};
    wclear(__TOOLSWND__);

    while (menu != NULL)
    {
        if(pos.x+strlen(menu->key)+strlen(menu->func) > __TOOLSWND__->_maxx) {
            break;
        }
        wtool_write(__TOOLSWND__, menu->key, menu->func, &pos);
        pos.x+=3;
        menu = menu->nextFunc;
    }
}

int wtool_write(WINDOW *wnd, char *key, char *func, point *pos)
{
    WINDOW *ckw, *dkw;

    ckw = derwin(wnd, 1, strlen(key), pos->y, pos->x);

    wmove(ckw, 0,0);
    wbkgd(ckw, wnd->_bkgd | A_REVERSE);
    wprintw(ckw, key);
    wrefresh(ckw);
    pos->x += strlen(key);
    
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
