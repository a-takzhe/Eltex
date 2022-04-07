#include "compare.h"

void init_color_pairs()
{
    start_color();
    init_color(TEXT_COLOR, 754, 669, 535);
    init_color(COLOR_BLACK, 100, 100, 100);
    init_color(CONTROL_BACK_COLOR, 400, 400, 400);
    init_pair(CMDWND_COLOR, COLOR_GREEN, CONTROL_BACK_COLOR);
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
    wmove(cmdinpwnd, 0,0);
    wrefresh(cmdinpwnd);

    cmdwnd = newwin(1, size.ws_col, size.ws_row-1, 0);
    wmove(cmdwnd, 0, 0);
    wprintw(cmdwnd, "F1 open file");
    wbkgd(cmdwnd, COLOR_PAIR(CMDWND_COLOR) | A_REVERSE);
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

int fill_cmdwnd(WINDOW* wnd)
{
    FILE* f;
    if((f = fopen(CMDWND_CONFIG, 'r')) == NULL) return -1;
    

    fclose(f);
}