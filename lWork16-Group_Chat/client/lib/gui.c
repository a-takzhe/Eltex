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
    init_color(BACK_1, 1000, 1000, 900);
    init_color(BACK_2, 1000, 1000, 1000);
    init_color(BACK_3, 1000, 1000, 950);
    init_color(BACK_4, 650, 700, 950);

    init_color(TEXT_1, 300, 300, 300);
    init_color(TEXT_2, 600, 600, 600);
    
    init_pair(CHAT_COLOR , TEXT_1, BACK_1);
    init_pair(USERS_COLOR, TEXT_1, BACK_2);
    init_pair(INPUT_COLOR, TEXT_1, BACK_3);
    init_pair(ERROR_COLOR, COLOR_RED, TEXT_2);
    init_pair(USER_LABEL_COLOR, TEXT_1, BACK_4);
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

    if((size.ws_row < H_MIN ||  size.ws_col < W_MIN) && wgetch(stdscr) == KEY_RESIZE){
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
        update_usr_area();
        
        if(wresize(CHAT_AREA, size.ws_row-3, size.ws_col-a) == -1){
            handle_error("CHAT_AREA resize");
        }
        if(mvwin(CHAT_AREA, 0, a) == -1){
            handle_error("CHAT_AREA move");
        }
        update_msg_area();

        if(wresize(INPUT_AREA, 3, size.ws_col-a) == -1){
            handle_error("CHAT_AREA resize");
        }
        if(mvwin(INPUT_AREA, size.ws_row-3, a) == -1){
            handle_error("CHAT_AREA move");
        }
        update_inp_area();
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

    INPUT_AREA = newwin(3, size.ws_col-a, size.ws_row-3, a);
    keypad(INPUT_AREA, true);
    res = wbkgd(INPUT_AREA, COLOR_PAIR(INPUT_COLOR));
    box(INPUT_AREA, '>', '-');

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

void set_ucolor(int pair, int color_num)
{
    init_color(color_num, rand()%200+800, rand()%400+600, rand()%600+400);
    init_pair (pair, TEXT_1, color_num);
}

int update_usr_area()
{
    wclear(USERS_AREA);
    for (size_t i = 0; i < MAX_USER; i++)
    {   
        if(users[i].active == 0){
            break;
        }
        WINDOW* wnd = derwin(USERS_AREA, 1, USERS_AREA->_maxx, i*2, 0);
        mvwprintw(wnd,0,0,"US > %s", users[i].name);
        wbkgd(wnd, COLOR_PAIR(USER_LABEL_COLOR));
    }
    wrefresh(USERS_AREA);
}

void print_mmes(const char* text, int line)
{
    int x = CHAT_AREA->_maxx-strlen(text)-5;
    mvwprintw(CHAT_AREA, line*2, x, "%s <(me)", text);
}
void print_mes(int uid, const char* text, int line)
{
    mvwprintw(CHAT_AREA, line*2, 0, "(%s)> %s", users[uid].name, text);
}

int update_msg_area()
{
    int cnt_msg = floor(CHAT_AREA->_maxy / 2.0);
    cnt_msg = cnt_msg > ID_LAST_MSG ? ID_LAST_MSG : cnt_msg;
    int line = 0;
    wclear(CHAT_AREA);
    for (int i = cnt_msg; i >= 0; i--)
    {
        if(messages[ID_LAST_MSG-i].u_id == -1){
            print_mmes(messages[ID_LAST_MSG-i].text, line);
        }
        else{
            print_mes(messages[ID_LAST_MSG-i].u_id, messages[ID_LAST_MSG-i].text, line);
        }
        line++;
    }
    wrefresh(CHAT_AREA);   
}

int update_inp_area()
{
    wclear(INPUT_AREA); 
    box(INPUT_AREA, '>', '-');
    mvwprintw(INPUT_AREA, 1, P(0), "%s", input_str);
    wrefresh(INPUT_AREA); 
}


