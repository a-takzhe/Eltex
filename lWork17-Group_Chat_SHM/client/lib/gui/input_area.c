#include "input_area.h"

void inp_init()
{
    keypad(INPUT_AREA, true);
    box(INPUT_AREA, '>', '-');
}

void update_inp_area()
{
    wclear(INPUT_AREA); 
    box(INPUT_AREA, '>', '-');
    mvwprintw(INPUT_AREA, 1, P(0), "%s", INPUT_STR);
    wrefresh(INPUT_AREA); 
}