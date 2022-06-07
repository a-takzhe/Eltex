#include "handler.h"

int main_handler()
{
    int key;
    char *ins_c;
    WINDOW* curw = __MAINWND__;
    isNote = 1;

    while (key = wgetch(curw))
    {
        if(key == KEY_F(3) || key == 0033){
            break;
        }
        if(menu_processing(key, &curw) == 1){
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
            case KEY_BACKSPACE:
                if(can_x(-1) == 0) break;
                back_click(curw);
                break;
            case 0012:
                if(can_y(+1) == 0) break;
                new_line();
                break;
            default:
                if(can_x(+1) == 0) break;
                wprintw(curw, "%c", key);    
                ins_c = insert((char)key);
                wprintw(curw, "%s", ins_c);
                inc_x();           
                break;
        }
        //wmove(curw, p.y, p.x);
        //chtype sym = winch(curw);
        
        if(curw == __HTOOLWND__){
            // wmove(__MAINWND__, __MAINWND__->_maxy, 0);
            // wprintw(__MAINWND__, "'%s' - %d", "BBB ", strlen("BBB "));
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
    if(CURMEN != __MENU__)
    {
        if(key == CTRL('X'))
        {
            menu_back(curw);
            return 1;
        }
        return 0;
    }

    if(key == CTRL('O')){return 1;}
    if(key == CTRL('S')){return 1;}

    MENU* tmp = get_menu_by_key(key, __MENU__);   
    if(tmp != NULL && tmp->isUseSubstr)
    {
        fill_toolbar(tmp->subMenu);
        to_menu(curw);
        return 1;
    }   
    return 0; 
}

void menu_back(WINDOW **curw)
{
    fill_toolbar(__MENU__);
    wclear(*curw);
    wrefresh(*curw);

    isNote = 1;
    clear_trow();

    *curw = __MAINWND__;
    PW = (point){.x = (*curw)->_curx, .y = (*curw)->_cury};
    wmove(*curw, PW.y, PW.x);
}

void to_menu(WINDOW **curw)
{
    isNote = 0;
    *curw = __HTOOLWND__;
    wmove(*curw, 0, 0);   
    wprintw(*curw, HTOOL_MES);
    wrefresh(*curw);
    PW = (point){.x = (*curw)->_curx, .y = (*curw)->_cury};
    PT = (point){.x=0, .y=0};
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
}

void inc_y()
{
    if(isNote)
    {
        if(PN.y < num_lines)
        {  
            PN.y++;
            if(get_symbol(PN.x, PN.y) == 0)
            {
                PN.x = (end_ind(PN.y)-1);
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
                PN.x = (end_ind(PN.y)-1);
            }
        }
    }
}

int clear_row(int r){
    int c = 0;
    while(NOTE[r][c] != 0){
        NOTE[r][c++] = 0;
    }
}

int delete_row()
{
    int r = PN.y;
    int c = 0;
    clear_row(r);
    while(strlen(NOTE[r+1]) != 0)
    {
        strcpy(NOTE[r], NOTE[r+1]);
        r++;
        c=0;
        while (NOTE[r][c] != 0)
        {
            NOTE[r][c++] = 0;
        }
    }
    num_lines--;
}

int back_click(WINDOW *wnd)
{
    if(PN.x == 0 && NOTE[PN.y][PN.x] == '\n')
    {
        delete_row();
        rewrite_mwnd(PN.y);
        PN.y--; PN.x = end_ind(PN.y)-1;
    }
    else if (PN.x != 0)
    {
        char* s = delete();
        dec_x();
        wmove(wnd, PN.y, PN.x);
        wprintw(wnd, "%s", s);
    }
    else
    {
        if(strlen(NOTE[PN.y-1]) + strlen(NOTE[PN.y]) < MAXCOL-2){
            int x = end_ind(PN.y-1)-1;
            strcpy(&NOTE[PN.y-1][x], NOTE[PN.y]);
            delete_row();
            PN.y--; PN.x = end_ind(PN.y)-1;
            rewrite_mwnd(PN.y);
        }
    }
    return 1;
}

int can_x(short v)
{
    if(v<0)
    {
       if(isNote){
           return (PN.x > 0) || (PN.y > 0);
       }
    }
    else if(v>0)
    {
        if(isNote){
           return (PN.x < MAXCOL-2  && strlen(NOTE[PN.y])+1 <= MAXCOL-2);
       }
    }
    return 0;
}

int can_y(short v)
{
    if(v > 0){
        return PN.y+1 < MAXROW;
    }
    else{
        return PN.y-1 >= 0;
    }
}

int new_line()
{
    int r = num_lines;
    while(r >= PN.y)
    {
        int c = 0;

        if(r != PN.y)
        {
            strcpy(NOTE[r+1], NOTE[r]);
        }
        else
        {
            strcpy(NOTE[r+1], &NOTE[r][PN.x]);
            NOTE[r][PN.x] = '\n';
            c = PN.x+1;
        }
        
        while(NOTE[r][c] != 0)
        {
            NOTE[r][c++] = 0;
        }
        r--;
    }
    rewrite_mwnd(PN.y);
    inc_y();
    PN.x = 0;
    num_lines++;
}