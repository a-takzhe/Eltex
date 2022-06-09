#ifndef COMPARE_H__
#define COMPARE_H__

#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <signal.h>
#include "read_config.h"
#include "data.h"

#define TEXT_COLOR 8
#define MAIN_BACK_COLOR 9
#define CONTROL_BACK_COLOR 10


MENU *__MENU__;
MENU *CURMEN;

struct winsize size;
short wdelta;


enum COLOR_SHEMA
{
    MAINWND_COLOR=1,
    TOOLSWND_COLOR=2,
    TEST_COLOR = 3
};



int init();
int fill_toolbar(MENU *menu);
int wend();
int rewrite_mwnd(int r);

#endif

