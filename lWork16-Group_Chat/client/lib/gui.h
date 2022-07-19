#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <string.h>

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
#define ERR_SCREEN_SIZE1 "I won't show you"
#define ERR_SCREEN_SIZE2 "increase the terminal (h,w)=(30,100)"
#define P(i) (i+3)

enum COLOR_SHEMA
{
    CHAT_COLOR  = 1,
    USERS_COLOR = 2,
    INPUT_COLOR = 3,
    ERROR_COLOR = 4,
    USER_COLOR = 5
};

struct GUI_USER_T{
    char* name;
    int colr_scheme;
} typedef gui_user;

int init();
int wend();
int input_user(char** users, int i);

