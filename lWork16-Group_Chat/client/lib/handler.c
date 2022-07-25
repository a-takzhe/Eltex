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

        switch (key)
        {
            case KEY_LEFT:
                dec_x();
                break;
            case KEY_RIGHT:
                inc_x();
                break;
            case KEY_ENTR:
                add_msg(input_str, -1);
                update_msg_area();
                //do something
                break;
            case KEY_BACKSPACE:
                if(can_x(-1) == 0) break;
                delete_symbol(w);
                break;
            default:
                if(can_x(1) == 0) break;
                wprintw(w, "%c", key);
                input_str[X]=key;
                inc_x();
                break;
        }
        // wmove(CHAT_AREA,17,0);
        // wclrtobot(CHAT_AREA);
        // wprintw(CHAT_AREA,"%c-%d", input_str[X], X);
        // wrefresh(CHAT_AREA);

        wmove(INPUT_AREA, 1, P(X));

    }
    return 0;
}

void inc_x()
{
    
    if(input_str[X] != 0 && X < INPUT_AREA->_maxx-2)
    {
        X++;
        wmove(INPUT_AREA, 1, P(X));
        wrefresh(INPUT_AREA);
    }
}

void dec_x()
{
    if(X > 0)
    {
        X--;
        wmove(INPUT_AREA, 1, P(X));
        wrefresh(INPUT_AREA);
    }
}

int can_x(int v)
{
    if(v>0){
        return (X < MAX_MSG_SIZE) && (X < INPUT_AREA->_maxx-2);
    }
    else{
        return X > 0;
    }
}

int end_ind()
{
    int i = 0;
    while (input_str[i] != 0)
    {
        i++;
    } 
    return --i;
}

char* mem_del_sym()
{
    int sl = strlen(&input_str[X]);
    char* bf = (char*)calloc(sl+1, sizeof(char));
    
    strncpy(bf, &input_str[X], sl+1);
    input_str[strlen(input_str)-1] = 0;
    strcpy(&input_str[X-1], bf);
    return bf;
}

void delete_symbol(WINDOW *wnd)
{
    char* s = mem_del_sym();
    dec_x();
    mvwprintw(wnd, 1, P(X), "%s ", s);
    free(s);
}


