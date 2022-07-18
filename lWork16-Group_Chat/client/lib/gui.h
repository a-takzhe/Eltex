#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <math.h>

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

WINDOW *CHAT_AREA;
WINDOW *USERS_AREA;
WINDOW *INPUT_AREA;

#define BACK_1 8
#define BACK_2 9
#define BACK_3 10
#define TEXT_1 11
#define TEXT_2 12
#define TEXT_3 13
// struct winsize size;


enum COLOR_SHEMA
{
    CHAT_COLOR  = 1,
    USERS_COLOR = 2,
    INPUT_COLOR = 3,
    ERROR_COLOR = 4
};

int init();
int wend();


