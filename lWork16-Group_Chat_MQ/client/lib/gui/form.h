#ifndef _GUI_H_
#define _GUI_H_

#include "input_area.h" 
#include "chat_area.h" 
#include "user_area.h" 

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

enum COLOR_SHEMA
{
    CHAT_COLOR  = 101,
    USERS_COLOR = 102,
    INPUT_COLOR = 103,
    ERROR_COLOR = 104,
    USER_COLOR  = 105
};

int init_w();
void allert_baner(struct winsize size);
void init_color_pairs();
void sig_winch(int signo);

int init();
int wend();

#endif