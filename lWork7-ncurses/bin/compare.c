#include "compare.h"

void init_color_pairs()
{
    start_color();
    init_color(TEXT_COLOR, 754, 669, 535);
    init_color(COLOR_BLACK, 100, 100, 100);
    init_color(CONTROL_BACK_COLOR, 400, 400, 400);
    init_pair(CMDWND_COLOR, COLOR_WHITE, CONTROL_BACK_COLOR);
    init_pair(MAINWND_COLOR, TEXT_COLOR, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_YELLOW);
}

int init_compare(int argc, char ** argv)
{
    initscr();
    keypad(stdscr, TRUE);
    signal(SIGWINCH, sig_winch);
    init_color_pairs();
    cbreak();
    refresh();

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    
    mainwnd = newwin(size.ws_row-1, size.ws_col, 0, 0);
    wbkgd(mainwnd, COLOR_PAIR(MAINWND_COLOR));
    wprintw(mainwnd, "Press any key to continue...");
    wrefresh(mainwnd);

    cmdinpwnd = derwin(mainwnd, 1,size.ws_col, size.ws_row - 2, 0);
    wrefresh(cmdinpwnd);

    cmdwnd = newwin(1, size.ws_col, size.ws_row-1, 0);
    wmove(cmdwnd, 0, 0);
    wbkgd(cmdwnd, COLOR_PAIR(CMDWND_COLOR));
    fill_cmdwnd(cmdwnd);
    wrefresh(cmdwnd);
}

int end_compare()
{
    delwin(mainwnd);
    delwin(cmdwnd);
    endwin();
}

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);

    if(wgetch(stdscr) == KEY_RESIZE)
    {
        wresize(mainwnd, size.ws_row-1, size.ws_col);
        wresize(cmdwnd, 1, size.ws_col);
        mvwin(cmdwnd,size.ws_row-1, 0);
        wrefresh(cmdwnd);
        wrefresh(mainwnd); 
    }
    // printw("Hello...: %d/%d/%d", wgetch(stdscr), KEY_RESIZE, signo);
    refresh();
}

void compare(char *ckey, char *dkey, WINDOW *wnd, int col)
{
    WINDOW *ckw, *dkw;
    wmove(wnd, 0, col);

    ckw = derwin(wnd, 1,2,0,col);
    dkw = dervin(wnd, 1,10,0,col+2);

    
} 

int fill_cmdwnd(WINDOW* wnd)
{

    FILE* f;
    int pos = 0;
    char buffer[20];
    char *key_dsc, *key_ch;

    if((f=fopen(CMDWND_CONFIG, "r")) == NULL)
    {
        wprintw(mainwnd, "cant open file\n");
        return -1;
    } 
    
    while ((fgets(buffer, 20, f)))
    {
        // wprintw(mainwnd, "fread symbols: %s", buffer);
        key_ch = strtok(buffer, ";");
        key_dsc = strtok(NULL,"");
        if(key_ch == NULL || key_dsc == NULL) continue;
        // wprintw(mainwnd, "\tch_key: %s\n", key_ch);
        // wprintw(mainwnd, "\tkey_dsc: %s\n", key_dsc);
    }
    wrefresh(mainwnd);
    refresh();

    fclose(f);
}