#include "gui.h"
//-------------------
//prototype function
//-------------------
//int write_t(WINDOW *wnd, char *key, char *func, point *pos);
void init_color_pairs();
void sig_winch(int signo);
int init_w();


//-------------------------
//function implementation
//-------------------------
void init_color_pairs()
{
    start_color();
    init_color(BACK_1, 1000, 1000, 700);
    init_color(BACK_2, 700, 1000, 1000);
    init_color(BACK_3, 1000, 800, 1000);

    init_color(TEXT_1, 300, 300, 300);
    
    init_pair(CHAT_COLOR , TEXT_1, BACK_1);
    init_pair(USERS_COLOR, TEXT_1, BACK_2);
    init_pair(INPUT_COLOR, TEXT_1, BACK_3);
    init_pair(ERROR_COLOR, COLOR_RED, TEXT_1);
}

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    refresh();

    if(wgetch(stdscr) == KEY_RESIZE)
    {
        // int a = floor((double)size.ws_col / 4.0);

        if(wresize(USERS_AREA, size.ws_row-2, 10) == -1){
            wend();
            handle_error("USERS_AREA resize");
        }
        if(mvwin(USERS_AREA, 0, 0) == -1){
            wend();
            handle_error("USERS_AREA mowe");
        }

        
        if(wresize(CHAT_AREA, size.ws_row-2, 10)==-1){
            wend();
            perror("wresize");
            exit(0);
        }
        if(mvwin(CHAT_AREA, 0, 15)==-1){
            wend();
            perror("mvwin");
            exit(0);
        }

        // wresize(__TOOLSWND__, 1, size.ws_col > MAXCOL ? MAXCOL : size.ws_col);
        // mvwin(__TOOLSWND__, size.ws_row-1, 0);

        // if(wdelta - size.ws_col <= -5)
        // {
        //     fill_toolbar(CURMEN);
        //     wdelta = size.ws_col;
        // }     
        // else if(wdelta - size.ws_col >= 0){
        //     wdelta = size.ws_col;
        // }  
    }
    wrefresh(USERS_AREA);
    wrefresh(CHAT_AREA);
    // wrefresh(__MAINWND__);
}

int init()
{
    if(stdscr != NULL || CHAT_AREA != NULL) { 
        wend();
    }
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);

    init_color_pairs();
    signal(SIGWINCH, sig_winch);
    
    if(init_w() == ERR) return ERR;
    return 0;
}

int init_w()
{
    struct winsize size;
    u_short res = 0;

    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);

    int a = floor((double)size.ws_col / 4.0);
    
    USERS_AREA = newwin(size.ws_row, 10, 0, 0);
    res = wbkgd(USERS_AREA, COLOR_PAIR(USERS_COLOR));
    
    CHAT_AREA = newwin(size.ws_row, 10, 0, 15);
    keypad(CHAT_AREA, true);
    res = wbkgd(CHAT_AREA, COLOR_PAIR(CHAT_COLOR));

    // __TOOLSWND__ = newwin(1, size.ws_col, size.ws_row-1, 0);
    // res = wbkgd(__TOOLSWND__, COLOR_PAIR(TOOLSWND_COLOR));
    // wdelta = size.ws_col;

    res = wrefresh(USERS_AREA);
    res = wrefresh(CHAT_AREA);

    // res = wrefresh(__TOOLSWND__);

    return res;
}

int wend()
{
    delwin(CHAT_AREA);
    delwin(USERS_AREA);
    delwin(INPUT_AREA);
    endwin();
}