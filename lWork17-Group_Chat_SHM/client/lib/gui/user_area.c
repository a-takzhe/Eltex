#include "user_area.h"

void update_usr_area()
{
    wclear(USERS_AREA);
    for (size_t i = 0; i < MAX_USERS; i++)
    {   
        if(USERS[i].active == -1)
            continue;
        
        WINDOW* wnd = derwin(USERS_AREA, 1, USERS_AREA->_maxx, i*2, 0);
        mvwprintw(wnd, 0, 0, "(%d) > %s", USERS[i].uid, USERS[i].name);
        wbkgd(wnd, COLOR_PAIR(USER_LABEL_COLOR));
    }
    wrefresh(USERS_AREA);
}

void set_ucolor(int pair, int color_num)
{
    init_color(color_num, rand()%200+800, rand()%400+600, rand()%600+400);
    init_pair (pair, 11, color_num);
}