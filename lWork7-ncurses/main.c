#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

WINDOW *mainwnd;
WINDOW *cwnd;
WINDOW *subwnd;

struct command{
    char* key;
    char* description;
};

enum COLOR_SHEMA
{
    MAINWND=1,
    CWND=2
};

void init_color_pairs()
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
}

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
    
    // attron();
    // move(0, 0);
    // printw("Hello...: (Y,X) (%d,%d)", size.ws_row, size.ws_col);
    // refresh();
}

int main(int argc, char ** argv)
{
    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    init_color_pairs();
    // mainwnd = newwin(5, 100, 5, 1);
    
    // box(mainwnd, '.', '.');
    // box(cwnd, '.', '.');
    
    // wbkgd(mainwnd, COLOR_PAIR(1) | A_BOLD);
    
    bkgd(COLOR_PAIR(3) | A_BOLD);
    refresh();
    // wrefresh(mainwnd);
    
    
    printw("Press any key to continue...");
    refresh();
    
    cwnd = newwin(2, 100, size.ws_row-2, 0);
    wmove(cwnd, 0, 0);
    wprintw(cwnd, "F1");
    wbkgd(cwnd, COLOR_PAIR(2));
    wrefresh(cwnd);

    subwnd = derwin(cwnd, 1, 10, 0, 3);
    wmove(subwnd, 0, 0);
    wprintw(subwnd, "open file");
    wbkgd(subwnd, COLOR_PAIR(1)|A_BOLD);
    wrefresh(subwnd);
    wrefresh(cwnd);
    
    getch();

    // wmove(mainwnd, 1, 1);
    // //wrefresh(mainwnd);
    // getch();

    // wmove(cwnd, 1, 1);
    // wrefresh(cwnd);
    // getch();
    // wnd = newwin(3, size.ws_col, size.ws_row-3, 0);
    // box(wnd, '|', '-');
    // //subwnd = derwin(wnd, 4, 16, 1, 1);
    // // wprintw(subwnd, "Hello, brave new curses world!\n");
    // wmove(wnd, 1,1);

    // wprintw(wnd, "F1 - open file");
    // wrefresh(wnd);
    // //delwin(subwnd);
    // delwin(wnd);
    // wattroff(wnd, COLOR_PAIR(1)|A_BOLD);
    
    delwin(mainwnd);
    delwin(cwnd);
    endwin();
    exit(EXIT_SUCCESS);
}