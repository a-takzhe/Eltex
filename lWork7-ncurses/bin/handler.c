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
        if(key >= CTRL('A') && key <= CTRL('z')){
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
            // case KEY_BACKSPACE:
            //     if(can_x(p, -1) == 0) break;
            //     back_click(curw, &p);
            //     break;
            // default:
            //     if(can_x(p, +1) == 0) break;
            //     wprintw(curw, "%c", key);    
            //     ins_c = insert(p.x, p.y, (char)key);
            //     wprintw(curw, "%s", ins_c);
            //     p.x++;            
            //     break;
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
            wprintw(__HTOOLWND__, "%c (%d-%d) (%d-%d)", (get_symbol(PN.x,PN.y)=='\n'?'_':get_symbol(PN.x,PN.y)),
                     PW.y, PW.x, PN.y, PN.x);
            wrefresh(__HTOOLWND__);    
        }
        

        wmove(curw, PW.y, PW.x);
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
        if(PN.x < (MAXCOL-2) && (get_symbol(PN.x+1, PN.y) != 0 || get_symbol(PN.x+2, PN.y) != 0))
        {
            if((PN.y)*(MAXCOL)+PN.x < __MAINWND__->_maxy*__MAINWND__->_maxx)
            {
                PN.x++;
                if(PW.x+1 > __MAINWND__->_maxx)
                {
                    PW.y++;
                    PW.x=0;
                }
                else{
                    PW.x++;
                }
            }
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
            if(PW.x!=0)
            {
                PW.x--;
            }
            else{
                PW.y--;
                PW.x = __MAINWND__->_maxx;
            }
        }
    }
}

void inc_y()
{
    if(isNote)
    {
        if(PN.y < LLN)
        {
            if((PN.y)*(MAXCOL)+PN.x < __MAINWND__->_maxy*__MAINWND__->_maxx)
            {
                int a = strlen(&NOTE[PN.y][PN.x]);
                int d = 0;
                PN.y++;
                if(get_symbol(PN.x, PN.y) == 0)
                {
                    d = PN.x - (end_ind(PN.y)-1);
                    PN.x -= d;
                }

                int more1 = a > __MAINWND__->_maxx - PW.x;
                int more2 = PN.x > __MAINWND__->_maxx;

                if( more1 || more2)
                {
                    if(more1)
                    {
                        int c = a-(__MAINWND__->_maxx - PW.x);
                        PW.y += c / __MAINWND__->_maxx + (c % __MAINWND__->_maxx > 0) + (!more2); 
                    }
                    if(more2)
                    {
                        PW.y += (PN.x) / (__MAINWND__->_maxx) + (PN.x % __MAINWND__->_maxx > 0 && PW.x != __MAINWND__->_maxx);
                    }
                }
                else
                {
                    PW.y++;
                }
                if(d != 0)
                {
                    if(PN.x > __MAINWND__->_maxx){
                        PW.x-=d;
                    }
                    else{
                        PW.x=strlen(NOTE[PN.y])-1;
                    }
                }
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
            int x=PN.x;
            int d = 0;
            PN.y--;
            if(get_symbol(PN.x, PN.y) == 0)
            {
                d = PN.x - (end_ind(PN.y)-1);
                PN.x -= d;
            }

            int a = strlen(&NOTE[PN.y][PN.x]);
            int more1 = x > __MAINWND__->_maxx;
            int more2 = a > __MAINWND__->_maxx - PW.x;

            if(more1 || more2)
            {
                if(more1)
                {
                    PW.y-= x / (__MAINWND__->_maxx) + (x % __MAINWND__->_maxx > 0 && PW.x != __MAINWND__->_maxx);
                }
                if(more2)
                {
                    int c = a-(__MAINWND__->_maxx - PW.x);
                    PW.y-= c / (__MAINWND__->_maxx) + (c % __MAINWND__->_maxx > 0)+(!more1);
                }
            } 
            else
            {
                PW.y--;
            }
            
            if(d != 0)
            {
                if(PN.x > __MAINWND__->_maxx){
                    PW.x-=d;
                }
                else{
                    PW.x=strlen(NOTE[PN.y])-1;
                }
            }
        }
    }
}



int back_click(WINDOW *wnd, point *p)
{
    char *ins_c = delete(p->x, 0);

    wmove(wnd, p->y, --p->x);
    wprintw(wnd, "%s", ins_c);
    wprintw(wnd, " ");
}

int change_x(point p, short v)
{
    // if(v<0)
    // {
    //     if(p->x > 0 && isNote == 1)
    //     {
    //         p->x--;
    //     } 
    //     else if(p->x - strlen(HTOOL_MES) > 0 && isNote == 0){
    //         p->x--; 
    //     }
    // }
    // else if(v>0)
    // {
    //     if(get_symbol(p->x+1,p->y) != 0 || get_symbol(p->x+2, p->y) != 0)
    //     {
    //         p->x++;
    //     }
    // }
    // return 1;
}

int change_y(point p, short v)
{
    // if(isNote == 0) return 1;

    // if(v<0){
    //     if(p->y > 0){
    //         p->y--;

    //         if(get_symbol(p->x, p->y) == 0)
    //         {
    //             p->x = end_ind(p->y)-1;
    //         }
    //     }
    // }
    // else if(v>0)
    // {
    //     if(p->y < LLN)
    //     {
    //         p->y++;
            
    //         if(p->y > __MAINWND__->_maxy){
    //             rewrite_mwnd(p->y - __MAINWND__->_maxy / 4);
    //         }
            
    //         if(get_symbol(p->x, p->y) == 0)
    //         {
    //             p->x = end_ind(p->y)-1;
    //         }
    //     }
    // }
    
    // return 1;
}

int can_x(point p, short v)
{
    if(v<0)
    {
        if(p.x > 0 && isNote == 1)
        {
            return 1;
        } 
        else if(p.x - strlen(HTOOL_MES) > 0 && isNote == 0)
        {
            return 1; 
        }
    }
    else if(v>0)
    {
        if(isNote && p.x < MAXCOL)
        {
            return 1;
        }
        else if(!isNote && p.x - strlen(HTOOL_MES) < MAXCOL2)
        {
            return 1;
        }
    }
    return 0;
}
