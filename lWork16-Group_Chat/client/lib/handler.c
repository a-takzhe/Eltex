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
                // dec_x();
                break;
            case KEY_RIGHT:
                // inc_x();
                break;
            case KEY_ENTER:
                //do something
                break;
            case KEY_BACKSPACE:
                // if(can_x(-1) == 0) break;
                //delete_symbol(curw);
                break;
            default:
                // if(can_x(+1) == 0) break;
                //insert_symbol(key, curw);
                break;
        }

        wprintw(w, "%c", key);
    }
    return 0;
}

// void inc_x()
// {
//     if(isNote)
//     {
//         if(PN.x < (MAXCOL-2) && PN.x < size.ws_col -1 && 
//            (get_symbol(PN.x, PN.y) != 0 && get_symbol(PN.x, PN.y) != NEW_LINE))
//         //    (get_symbol(PN.x+1, PN.y) != 0 || get_symbol(PN.x+2, PN.y) != 0))
//         {
//             PN.x++;
//         }
//     }
//     else
//     {
//         if(get_symbol(PN.x, PN.y) != 0 && (PN.x-strlen(HTOOL_MES) < MAXCOL2-2))
//         {
//             PN.x++;
//         }
//     }
// }

// void dec_x()
// {
//     if(isNote)
//     {
//         if(PN.x>0)
//         {
//             PN.x--;
//         }
//     }
//     else
//     {
//         if(PN.x - strlen(HTOOL_MES) > 0)
//         {
//             PN.x--;
//         }
//     }
// }

// int can_x(short v)
// {
//     if(v<0)
//     {
//        if(isNote){
//            return (PN.x > 0) || (PN.y > 0);
//        }
//        else{
//            return PN.x > strlen(HTOOL_MES);
//        }
//     }
//     else if(v>0)
//     {
//         if(isNote){
//            return (PN.x < MAXCOL-2  && strlen(NOTE[PN.y])+1 <= MAXCOL-2);
//         }
//         else{
//             return (strlen(TROW)+1 <= MAXCOL2-2);
//         }
//
//     }
//     return 0;
// }





