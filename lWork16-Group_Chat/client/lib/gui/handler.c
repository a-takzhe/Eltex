#include "handler.h"

int h_main()
{
    int key, err;
    WINDOW* w = INPUT_AREA;
    wmove(w, 1, P(0));

    while (key = wgetch(w))
    {
        if(key == KEY_F(3) || key == 0033){
            err = pthread_cancel(pth_listener);
            if(err != 0)
                handle_error_en(err, "pthread_cancel");
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
                sync_add_msg(INPUT_STR, -1);
                send_msg(INPUT_STR);
                clear_input();
                update_inp_area();
                break;
            case KEY_BACKSPACE:
                if(can_x(-1) == 0) break;
                delete_symbol(w);
                break;
            default:
                if(can_x(1) == 0) break;
                wprintw(w, "%c", key);
                INPUT_STR[X]=key;
                inc_x();
                break;
        }

        wmove(INPUT_AREA, 1, P(X));

    }
    return 0;
}

void inc_x()
{
    
    if(INPUT_STR[X] != 0 && X < INPUT_AREA->_maxx-2)
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
    while (INPUT_STR[i] != 0)
    {
        i++;
    } 
    return --i;
}

char* mem_del_sym()
{
    int sl = strlen(&INPUT_STR[X]);
    char* bf = (char*)calloc(sl+1, sizeof(char));
    
    strncpy(bf, &INPUT_STR[X], sl+1);
    INPUT_STR[strlen(INPUT_STR)-1] = 0;
    strcpy(&INPUT_STR[X-1], bf);
    return bf;
}

void delete_symbol(WINDOW *wnd)
{
    char* s = mem_del_sym();
    dec_x();
    mvwprintw(wnd, 1, P(X), "%s ", s);
    free(s);
}


