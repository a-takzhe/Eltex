#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>

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
    WINDOW * wnd;
    WINDOW * subwnd;
    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0);
    refresh();

    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);

    wnd = newwin(3, size.ws_col, size.ws_row-3, 0);
    box(wnd, '|', '-');
    //subwnd = derwin(wnd, 4, 16, 1, 1);
    // wprintw(subwnd, "Hello, brave new curses world!\n");
    wmove(wnd, 1,1);

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_YELLOW);
    wattron(wnd, COLOR_PAIR(1));
    wprintw(wnd, "F1 - open file");
    wrefresh(wnd);
    //delwin(subwnd);
    delwin(wnd);
    wattroff(wnd, COLOR_PAIR(1));
    
    move(0, 0);
    printw("Press any key to continue...");
    refresh();
    getch();
    endwin();
    exit(EXIT_SUCCESS);
}