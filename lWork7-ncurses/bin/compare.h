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


WINDOW *__MAINWND__;
WINDOW *__HTOOLWND__;
WINDOW *__TOOLSWND__;
MENU *__MENU__;
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

int init(WINDOW* mainw, WINDOW* toolsw, WINDOW* htoolw, MENU* menu);
int fill_toolbar(MENU *menu);
int wend();
