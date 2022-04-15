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


extern WINDOW *__MAINWND__;
extern WINDOW *__HTOOLWND__;
extern WINDOW *__TOOLSWND__;
short wdelta;

enum COLOR_SHEMA
{
    MAINWND_COLOR=1,
    TOOLSWND_COLOR=2
};


struct POINT
{
    unsigned short int x;
    unsigned short int y;
};

void init_color_pairs();
void sig_winch(int signo);

int init();
int init_w();
int set_default_tools();

int wtool_write(WINDOW *wnd, char *ckey, char *dkey, struct POINT *pos);
int wend();
