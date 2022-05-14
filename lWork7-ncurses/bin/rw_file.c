#include "rw_file.h"

int read_file(char *path, WINDOW* wnd, char c[255][255])
{
    FILE* f;
    char buffer[1024];  
    if((f = fopen(path, "r")) == NULL)
    {
        return 1;
    }

    wmove(wnd,0,0);
    c[0][0] = 'L';

    while((fread(buffer, sizeof(char), 1024, f)) != 0)
    {
        wprintw(wnd, "%s", buffer);

    }
    wrefresh(wnd);

    fclose(f);
}