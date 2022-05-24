#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <signal.h>
#include "read_config.h"


#define TEXT_COLOR 8
#define MAIN_BACK_COLOR 9
#define CONTROL_BACK_COLOR 10


#define HTOOL_MES "[Insert File Name]: "
#define MAXCOL 256
#define MAXCOL2 64
#define MAXROW 128

typedef struct PNT
{
    unsigned short x;
    unsigned short y;
    unsigned short max_X, max_y;
} point;

WINDOW *__MAINWND__;
WINDOW *__HTOOLWND__;
WINDOW *__TOOLSWND__;
MENU *__MENU__;
MENU *CURMEN;
short wdelta;

char NOTE[MAXROW][MAXCOL];
char TROW[MAXCOL2];
point PN, PT, PW;

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

