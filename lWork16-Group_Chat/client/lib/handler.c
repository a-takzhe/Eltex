#include "handler.h"

int h_main()
{
    int key;
    WINDOW* w = INPUT_AREA;
    wmove(w, 1, P(0));

    while (key = wgetch(w))
    {
        if(key == KEY_F(3) || key == 0033){
            break;
        }
        if(key == KEY_F0) {
            waddstr(w,"F0");
            continue;
        }
        if(key >= CTRL('A') && key <= CTRL('z') && key != 0012){
            continue;
        }
        wprintw(w, "%c", key);
    }
    return 0;
}
