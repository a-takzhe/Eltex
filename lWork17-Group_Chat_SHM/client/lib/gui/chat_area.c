#include "chat_area.h"

void print_mmes(const char* text, int line)
{
    int x = CHAT_AREA->_maxx-strlen(text)-5;
    mvwprintw(CHAT_AREA, line*2, x, "%s <(me)", text);
}

void print_mes(char* name, const char* text, int line)
{
    // int i;
    // for (i = 0; i < MAX_USER; i++)
    // {
    //     if(USERS[i].uid == uid){
    //         break;
    //     }
    // }
    
    mvwprintw(CHAT_AREA, line*2, 0, "(%s)> %s", name, text);
}

void update_msg_area()
{
    int line = 0;
    int cnt_msg = floor(CHAT_AREA->_maxy / 2.0);
    cnt_msg = cnt_msg > ID_LAST_MSG ? ID_LAST_MSG : cnt_msg;
    
    wclear(CHAT_AREA);
    for (int i = cnt_msg; i >= 0; i--)
    {
        if(MESSAGES[ID_LAST_MSG-i].u_id == -1)
        {
            print_mmes(MESSAGES[ID_LAST_MSG-i].text, line);
        }
        else
        {
            print_mes(MESSAGES[ID_LAST_MSG-i].name, MESSAGES[ID_LAST_MSG-i].text, line);
        }
        line++;
    }
    wrefresh(CHAT_AREA);   
}