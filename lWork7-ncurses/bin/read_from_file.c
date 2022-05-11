#include "read_from_file.h"

int read_file(char *path, WINDOW* wnd)
{
    FILE* f;
    char buffer[1024];  
    f = fopen(path, "r");

    wmove(wnd,0,0);
    while((fread(buffer, sizeof(char), 1024, f)) != 0)
    {
        wprintw(wnd, "%s", buffer);
    }
    wrefresh(wnd);

    fclose(f);
}