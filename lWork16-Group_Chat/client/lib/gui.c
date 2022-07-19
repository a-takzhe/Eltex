#include "gui.h"
//-------------------
//prototype function
//-------------------
//int write_t(WINDOW *wnd, char *key, char *func, point *pos);
void init_color_pairs();
void sig_winch(int signo);
int init_w();
void allert_baner(struct winsize size);


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
    init_color(TEXT_2, 600, 600, 600);
    
    init_pair(CHAT_COLOR , TEXT_1, BACK_1);
    init_pair(USERS_COLOR, TEXT_1, BACK_2);
    init_pair(INPUT_COLOR, TEXT_1, BACK_3);
    init_pair(ERROR_COLOR, COLOR_RED, TEXT_2);
}

void allert_baner(struct winsize size)
{
    wclear(CHAT_AREA);

    if(wresize(CHAT_AREA, size.ws_row, size.ws_col) == -1){
        handle_error("CHAT_AREA resize");
    }
    if(mvwin(CHAT_AREA, 0, 0) == -1){
        handle_error("CHAT_AREA move");
    }

    wmove(CHAT_AREA, size.ws_row/2, size.ws_col/2 - strlen(ERR_SCREEN_SIZE1)/2);
    wprintw(CHAT_AREA, ERR_SCREEN_SIZE1);
    wmove(CHAT_AREA, size.ws_row/2+1, size.ws_col/2-strlen(ERR_SCREEN_SIZE2)/2);
    wprintw(CHAT_AREA, ERR_SCREEN_SIZE2);
    wbkgd(CHAT_AREA, COLOR_PAIR(ERROR_COLOR));
    wrefresh(CHAT_AREA);
    wclear(CHAT_AREA);
    wbkgd(CHAT_AREA, COLOR_PAIR(CHAT_COLOR));
}

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    refresh();

    if((size.ws_row < 20 ||  size.ws_col < 80)&&wgetch(stdscr) == KEY_RESIZE){
        allert_baner(size);
        return;
    }

    if(wgetch(stdscr) == KEY_RESIZE)
    {
        int a = size.ws_col / 4.0;

        wclear(USERS_AREA);
        if(wresize(USERS_AREA, size.ws_row, a) == -1){
            handle_error("USERS_AREA resize");
        }
        
        if(wresize(CHAT_AREA, size.ws_row-3, size.ws_col-a) == -1){
            handle_error("CHAT_AREA resize");
        }
        if(mvwin(CHAT_AREA, 0, a) == -1){
            handle_error("CHAT_AREA move");
        }

        if(wresize(INPUT_AREA, 3, size.ws_col-a) == -1){
            handle_error("CHAT_AREA resize");
        }
        if(mvwin(INPUT_AREA, size.ws_row-3, a) == -1){
            handle_error("CHAT_AREA move");
        }  
    }
    wrefresh(CHAT_AREA);
    wrefresh(USERS_AREA);
    wrefresh(INPUT_AREA);
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
    
    USERS_AREA = newwin(size.ws_row, a, 0, 0);
    res = wbkgd(USERS_AREA, COLOR_PAIR(USERS_COLOR));
    
    CHAT_AREA = newwin(size.ws_row-3, size.ws_col-a, 0, a);
    res = wbkgd(CHAT_AREA, COLOR_PAIR(CHAT_COLOR));

    INPUT_AREA = newwin(3, size.ws_col, size.ws_row-3, a);
    keypad(INPUT_AREA, true);
    res = wbkgd(INPUT_AREA, COLOR_PAIR(INPUT_COLOR));
    mvwprintw(INPUT_AREA, 1, 0, ">>>");

    res = wrefresh(USERS_AREA);
    res = wrefresh(CHAT_AREA);
    res = wrefresh(INPUT_AREA);

    return res;
}

int wend()
{
    delwin(CHAT_AREA);
    delwin(USERS_AREA);
    delwin(INPUT_AREA);
    endwin();
}

void set_ucolor(int pair){
    init_color(14, rand()%1000, rand()%1000, rand()%1000);
    init_pair (pair, TEXT_1, 14);
}

int input_user(char** users, int N)
{
    wclear(USERS_AREA);
    for (size_t i = 0; i < N; i++)
    {
        WINDOW* wnd = derwin(USERS_AREA, 1, USERS_AREA->_maxx, i*2, 0);
        mvwprintw(wnd,0,0,"US > %s", users[i]);
    }
    wrefresh(USERS_AREA);
}




