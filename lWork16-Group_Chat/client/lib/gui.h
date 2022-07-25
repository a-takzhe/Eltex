#ifndef _GUI_H_
#define _GUI_H_

#include "../../common.h"

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

enum COLOR_SHEMA
{
    CHAT_COLOR  = 101,
    USERS_COLOR = 102,
    INPUT_COLOR = 103,
    ERROR_COLOR = 104,
    USER_COLOR  = 105,
    USER_LABEL_COLOR = 106
};

int init();
int wend();
int update_usr_area();
int update_msg_area();
int update_inp_area();



#endif