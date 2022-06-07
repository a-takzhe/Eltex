#include "rw_file.h"


int read_file(char *path, WINDOW* wnd)
{
    FILE* f;
    char buffer[MAXCOL] = {0};
    int ln=0;
    int sz;

    if((f = fopen(path, "r")) == NULL)
    {
        return 1;
    }

    fseek(f, 0L, SEEK_END);
    if(ftell(f) > MAXCOL*MAXROW)
    {
        wend();
        printf("file %s (%ldbt) is too large\n", path, ftell(f));
        return -1;
    }
    fseek(f, 0L, SEEK_SET);

    wclear(wnd);
    wmove(wnd,0,0);

    while((fgets(buffer, MAXCOL, f)) != 0 && ln < MAXROW)
    {
        strncpy(NOTE[ln], buffer, MAXCOL);
        if(ln < wnd->_maxy)
        {
            wprintw(wnd, "%s", buffer);
        } 
        ln++;
    }
    wmove(wnd,0,0);
    wrefresh(wnd);
    num_lines = ln-1<0?0:ln-1;

    fclose(f);
    
    return 1;
}

