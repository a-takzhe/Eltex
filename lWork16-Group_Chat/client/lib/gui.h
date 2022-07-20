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
#define BACK_4 14

#define ERR_SCREEN_SIZE1 "I won't show you"
#define ERR_SCREEN_SIZE2 "increase the terminal (h,w)=(20,80)"
#define H_MIN 20
#define W_MIN 80


#define MAX_USER 10
#define MAX_MSG_SIZE 64
#define MAX_MSG 64

enum COLOR_SHEMA
{
    CHAT_COLOR  = 101,
    USERS_COLOR = 102,
    INPUT_COLOR = 103,
    ERROR_COLOR = 104,
    USER_COLOR = 105,
    USER_LABEL_COLOR = 106
};

struct GUI_USER_T{
    char* name;
    int active;
} typedef gui_user;
gui_user users[MAX_USER]; 


char input_str[MAX_MSG_SIZE];
int X;
struct MESSAGE_LIST_T{
    char* text;
    int u_id;
} typedef message_list;
message_list messages[MAX_MSG];
int ID_LAST_MSG;



int init();
int wend();
int update_user_area();
int update_msg_area();
