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
            set_default_tools();
            wdelta = size.ws_col;
        }     
        else if(wdelta - size.ws_col > 0){
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
    if(stdscr != NULL || __MAINWND__ != NULL)
    {
        wend();
    }

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    init_color_pairs();
    signal(SIGWINCH, sig_winch);
    refresh();
    
    if(init_w() == ERR);
    if(set_default_tools() == ERR);
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

int set_default_tools()
{
    FILE* f;
    struct POINT pos = {.x=0, .y=0};
    char buffer[20];
    char *key_dsc, *key_ch;

    if((f=fopen(CMDWND_CONFIG, "r")) == NULL)
    {
        return ERR;
    } 

    wclear(__TOOLSWND__);
    while ((fgets(buffer, 20, f)))
    {
        key_ch = strtok(buffer, ":");
        key_dsc = strtok(NULL,"");

        if(key_ch == NULL || key_dsc == NULL) continue;
        
        wtool_write(__TOOLSWND__, key_ch, key_dsc, &pos);
        pos.x+=2;
    }

    fclose(f);
}

int wtool_write(WINDOW *wnd, char *ckey, char *dkey, struct POINT *pos)
{
    WINDOW *ckw, *dkw;

    ckw = derwin(wnd, 1, strlen(ckey), pos->y, pos->x);

    wmove(ckw, 0,0);
    wbkgd(ckw, wnd->_bkgd | A_REVERSE);
    wprintw(ckw, ckey);
    wrefresh(ckw);
    pos->x += strlen(ckey);
    
    wmove(wnd, pos->y, pos->x);
    wprintw(wnd,":%s", dkey);
    pos->x += strlen(dkey);
    wrefresh(wnd);
} 

int wend()
{
    delwin(__MAINWND__);
    delwin(__HTOOLWND__);
    delwin(__TOOLSWND__);
    endwin();
}
