#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <signal.h>
#include "read_config.h"


#define TEXT_COLOR 8
#define MAIN_BACK_COLOR 9
#define CONTROL_BACK_COLOR 10


extern WINDOW *__MAINWND__;
extern WINDOW *__HTOOLWND__;
extern WINDOW *__TOOLSWND__;
extern MENU *__MENU__;
MENU* CMENU;
short wdelta;

enum COLOR_SHEMA
{
    MAINWND_COLOR=1,
    TOOLSWND_COLOR=2,
    TEST_COLOR = 3
};

typedef struct PNT
{
    unsigned short int x;
    unsigned short int y;
} point;

void init_color_pairs();
void sig_winch(int signo);

int init();
int init_w();
int fill_tools(MENU *menu);

int wtool_write(WINDOW *wnd, char *key, char *func, point *pos);
int wend();
