#include "handler.h"

int main_handler()
{
    int key;
    isNote = 1;
    WINDOW* curw = __MAINWND__;
    wmove(curw, PN.y, PN.x);
    wrefresh(curw);

    while (key = wgetch(curw))
    {
        if(key == KEY_F(3) || key == 0033){
            break;
        }
        if(menu_processing(key, &curw)){
            continue;            
        }
        if(key >= CTRL('A') && key <= CTRL('z') && key != 0012){
            continue;
        }
        
        switch (key)
        {
            case KEY_DOWN:
                inc_y();
                break;
            case KEY_UP:
                dec_y();
                break;
            case KEY_LEFT:
                dec_x();
                break;
            case KEY_RIGHT:
                inc_x();
                break;
            case NEW_LINE:
                if(can_y(+1) == 0) break;
                if(new_line() == 0) break;
                break;
            case KEY_BACKSPACE:
                if(can_x(-1) == 0) break;
                delete_symbol(curw);
                break;
            default:
                if(can_x(+1) == 0) break;
                insert_symbol(key, curw);
                break;
        }
        
        if(curw == __HTOOLWND__)
        {
            // wmove(__MAINWND__, 10, 0);
            // wprintw(__MAINWND__, "%c (%d-%d)", get_cur_symbol(), PN.y, PN.x);
            // wrefresh(__MAINWND__);
        }
        else{
            wclear(__HTOOLWND__);
            wmove(__HTOOLWND__, 0, 0);
            wprintw(__HTOOLWND__, "%c (%o-%d) (%d-%d)", (get_symbol(PN.x,PN.y)=='\n'?'_':get_symbol(PN.x,PN.y)),
                     key, size.ws_col, PN.y, PN.x);
            wrefresh(__HTOOLWND__);    
        }
        

        wmove(curw, PN.y, PN.x);
        wrefresh(curw);
    }
}

int menu_processing(int key, WINDOW **curw)
{
    if(key == CTRL('X')){
        if(CURMEN != __MENU__){
            to_note(curw, 1);
            return 1;
        }
        return 0;
    }
    else if(key == 0012)
    {
        if(strstr(CURMEN->func, "Open") && strlen(TROW) > 0)
        {
            if(read_file(TROW) == 1)
            {
                to_note(curw, 0);
                return 1;
            }
        }
        return 0;
    }
    else if(key == CTRL('S')){
        return 1;
    }

    MENU* tmp = get_menu_by_key(key, __MENU__);   
    if(tmp != NULL && tmp->isUseSubstr)
    {
        fill_toolbar(tmp->subMenu);
        to_menu(curw);
        return 1;
    }   
    return 0; 
}

void to_note(WINDOW **curw, int fl)
{
    fill_toolbar(__MENU__);
    wclear(*curw);
    wrefresh(*curw);
    clear_trow(0);

    isNote = 1;
    *curw = __MAINWND__;
    if(fl == 0){
        PN = (point){.x = 0, .y = 0};
    }
    else{
        PN = (point){.x = (*curw)->_curx, .y = (*curw)->_cury};
    }
    wmove(*curw, PN.y, PN.x);
}

void to_menu(WINDOW **curw)
{
    isNote = 0;
    *curw = __HTOOLWND__;
    wmove(*curw, 0, 0);   
    wprintw(*curw, HTOOL_MES);
    write_fname(*curw);
    wrefresh(*curw);
    PN = (point){.x = (*curw)->_curx, .y = 0};
}


void inc_x()
{
    if(isNote)
    {
        if(PN.x < (MAXCOL-2) && PN.x < size.ws_col -1 && 
           (get_symbol(PN.x+1, PN.y) != 0 || get_symbol(PN.x+2, PN.y) != 0))
        {
            PN.x++;
        }
    }
    else
    {
        if(get_symbol(PN.x, PN.y) != 0 && (PN.x-strlen(HTOOL_MES) < MAXCOL2-2))
        {
            PN.x++;
        }
    }
}

void dec_x()
{
    if(isNote)
    {
        if(PN.x>0)
        {
            PN.x--;
        }
    }
    else
    {
        if(PN.x - strlen(HTOOL_MES) > 0)
        {
            PN.x--;
        }
    }
}

void inc_y()
{
    if(isNote)
    {
        if(PN.y < num_lines && PN.y < __MAINWND__->_maxy)
        {  
            PN.y++;
            if(get_symbol(PN.x, PN.y) == 0)
            {
                PN.x = (end_ind(PN.y));
            }
        }
    }
}

void dec_y()
{
    if(isNote)
    {
        if(PN.y > 0)
        {
            PN.y--;
            if(get_symbol(PN.x, PN.y) == 0)
            {
                PN.x = (end_ind(PN.y));
            }
        }
    }
}

int can_x(short v)
{
    if(v<0)
    {
       if(isNote){
           return (PN.x > 0) || (PN.y > 0);
       }
       else{
           return PN.x > strlen(HTOOL_MES);
       }
    }
    else if(v>0)
    {
        if(isNote){
           return (PN.x < MAXCOL-2  && strlen(NOTE[PN.y])+1 <= MAXCOL-2);
        }
        else{
            return (strlen(TROW)+1 <= MAXCOL2-2);
        }

    }
    return 0;
}

int can_y(short v)
{
    if(!isNote)
    {
        return 0;
    }
    if(v > 0)
    {
        return PN.y+1 < MAXROW;
    }
    else
    {
        return PN.y-1 >= 0;
    }
}


int new_line()
{
    if(isNote)
    {
        if(mem_new_line() == 0)
        {
            return 0;
        }
        rewrite_mwnd(PN.y);
        PN.x = 0;
        inc_y();

        return 1;
    }

    return 0;
}

void insert_symbol(int key, WINDOW* wnd)
{
    char* ss = mem_ins_sym((char)key);
    wprintw(wnd, "%c%s", key, ss);
    inc_x();           
}

void delete_symbol(WINDOW *wnd)
{
    if (PN.x != 0)
    {
        char* s = mem_del_sym();
        dec_x();
        wmove(wnd, PN.y, PN.x);
        wprintw(wnd, "%s", s);
        if(!isNote){wprintw(wnd," ");}
    }
    else
    {
        int x = mem_del_row(); 
        if(x != ERR)
        {
            dec_y();
            rewrite_mwnd(PN.y);
            PN.x = x;
        }
    }
}

