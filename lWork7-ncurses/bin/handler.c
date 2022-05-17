#include "handler.h"

int change_x(WINDOW *wnd, point *p, short v)
{
    if(v<0)
    {
        if(p->x > 0 && isNote == 1)
        {
            p->x--;
        } 
        else if(p->x - strlen(HTOOL_MES) > 0 && isNote == 0){
            p->x--; 
        }
    }
    else if(v>0)
    {
        if(get_symbol(p->x+1,p->y) != 0 || 
            get_symbol(p->x+2, p->y) != 0)
        {
            p->x++;
        }
    }
    return 1;
}

int change_y(point *p, short v)
{
    if(isNote == 0) return 1;

    if(v<0){
        if(p->y > 0){
            p->y--;

            if(get_symbol(p->x, p->y) == 0)
            {
                p->x = end_ind(p->y)-1;
            }
        }
    }
    else if(v>0){
        if(p->y < LLN){
            p->y++;

            if(get_symbol(p->x, p->y) == 0)
            {
                p->x = end_ind(p->y)-1;
            }
        }
    }
    
    return 1;
}

int main_handler()
{
    int key;
    char *ins_c;
    WINDOW* curw = __MAINWND__;
    point p = {.x = curw->_curx, .y = curw->_cury};
    isNote = 1;

    while (key = wgetch(curw))
    {
        if(key == KEY_F(3) || key == 0033){
            break;
        }
        if(menu_processing(key, &curw, &p) == 1){
            continue;            
        }
        if(key >= CTRL('A') && key <= CTRL('z')){
            //nwrite(curw);
            continue;
        }
        
        switch (key)
        {
            case KEY_DOWN:
                change_y(&p, +1);
                break;
            case KEY_UP:
                change_y(&p, -1);
                break;
            case KEY_LEFT:
                change_x(curw, &p, -1);
                break;
            case KEY_RIGHT:
                change_x(curw, &p, +1);
                break;
            // case KEY_BACKSPACE:
            //     // ins_c = delete(p.x, p.y);
            //     wmove(curw, p.y, --p.x);
            //     // wprintw(curw, "%s", ins_c);
            //     wprintw(curw, " ");
            //     break;
            // default:
            //     wprintw(curw, "%c", key);    
            //     // ins_c = insert(curw,__HTOOLWND__, p.x, p.y,(char)key);
            //     // wprintw(curw, "%s", ins_c);
            //     p.x++;            
            //     break;
            default:
                break;
        }
        wmove(curw, p.y, p.x);
        chtype sym = winch(curw);
        
        if(curw == __HTOOLWND__){
            // wmove(__MAINWND__, __MAINWND__->_maxy, 0);
            // wprintw(__MAINWND__, "'%s' - %d", "BBB ", strlen("BBB "));
            // wrefresh(__MAINWND__);
        }
        else{
            // wclear(__HTOOLWND__);
            // wmove(__HTOOLWND__, 0, 0);
            // wprintw(__HTOOLWND__, "'%c' - %d", get_symbol(p.x,p.y), get_symbol(p.x,p.y));
            // wrefresh(__HTOOLWND__);    
        }
        

        wmove(curw, p.y, p.x);
        wrefresh(curw);
    }
}

int menu_processing(int key, WINDOW **curw, point* p)
{
    if(CURMEN != __MENU__)
    {
        if(key == CTRL('X'))
        {
            fill_toolbar(__MENU__);
            wclear(*curw);
            wrefresh(*curw);
            *curw = __MAINWND__;
            isNote = 1;
            *p = (point){.x = (*curw)->_curx, .y = (*curw)->_cury};
            wmove(*curw, p->y, p->x);

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

        *curw = __HTOOLWND__;
        isNote = 0;
        wmove(*curw, 0, 0);   
        wprintw(*curw, HTOOL_MES);
        wrefresh(*curw);
        *p = (point){.x = (*curw)->_curx, .y = (*curw)->_cury};
        return 1;
    }   
    return 0; 
}
