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
        wprintw(w, "%c",key);
    }
    wend();

    puts("hello from client");
    return 0;
}