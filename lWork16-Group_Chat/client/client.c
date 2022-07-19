#include <stdio.h>
#include "./lib/gui.h"

int main()
{
    srand ( time(NULL) ); 
    setlocale(LC_ALL, "");
    init();
    
    int key;
    WINDOW* w = INPUT_AREA;
    char *u[] = {"alex","tomas","luke"}; 
    input_user(u,3);
    
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
        wprintw(w, "%o-%c|",key, key);
    }
    wend();

    puts("hello from client");
    return 0;
}