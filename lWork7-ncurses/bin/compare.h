#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <signal.h>


#define TEXT_COLOR 8
#define MAIN_BACK_COLOR 9
#define CONTROL_BACK_COLOR 10

#define CMDWND_CONFIG "./configure/cmd.config"
//#define CMDWND_CONFIG "./compare.h"

WINDOW *mainwnd;
WINDOW *cmdwnd;
WINDOW *cmdinpwnd;

enum COLOR_SHEMA
{
    MAINWND_COLOR=1,
    CMDWND_COLOR=2
};


void init_color_pairs();
void sig_winch(int signo);
int init_compare(int argc, char ** argv);
int end_compare();
int fill_cmdwnd(WINDOW* wnd);