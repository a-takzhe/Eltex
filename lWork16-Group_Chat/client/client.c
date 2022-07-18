#include <stdio.h>
#include "./lib/gui.h"

int main()
{
    setlocale(LC_ALL, "");
    init();
    
    int key;
    wmove(CHAT_AREA, 0, 0);
    wrefresh(CHAT_AREA);

    while (key = wgetch(CHAT_AREA))
    {
        if(key == KEY_F(3) || key == 0033){
            break;
        }
        wprintw(CHAT_AREA, "%c",key);
    }
    wend();

    puts("hello from client");
    return 0;
}