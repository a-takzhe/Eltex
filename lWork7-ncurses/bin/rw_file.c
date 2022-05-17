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

    wclear(wnd);
    wmove(wnd,0,0);

    while((fgets(buffer, MAXCOL, f)) != 0)
    {
        strncpy(NOTE[ln], buffer, MAXCOL);
        wprintw(wnd, "%s", buffer);
        ln++;
    }
    wmove(wnd,0,0);
    wrefresh(wnd);
    LLN = ln-1;

    fclose(f);
}

int nwrite(WINDOW* wnd)
{
    int ln=0;
    while(ln<=LLN)
    {
        wprintw(wnd, "%s", NOTE[ln]);
        ln++;
    }
    wrefresh(wnd);
}

char* insert(WINDOW* wnd, WINDOW* wnd2, int x, int y, char c)
{
    wclear(wnd2);
    if(NOTE[y][x] == 0)
    {
        NOTE[y][x] = c;
        return "";
    }

    int sl = strlen(&NOTE[y][x]);
    char* bf = (char*)malloc(sizeof(char)*sl+1);
    
    strncpy(bf, &NOTE[y][x], sl+1);
    NOTE[y][x]=c;
    strcpy(&NOTE[y][++x], bf);   

    // wmove(wnd2, 0, 0);
    // wprintw(wnd2, "len: %d  str: %s|", sl, bf);
    // wrefresh(wnd2);

    return bf;
}

char* delete(int x, int y)
{
    int i = x;
    int sl = strlen(&NOTE[y][x]);
    char* bf = (char*)malloc(sizeof(char)*sl+1);
    strncpy(bf, &NOTE[y][x], sl+1);

    while(NOTE[y][i] != 0){
        NOTE[y][i] = 0;
        i++;
    }
    strcpy(&NOTE[y][--x], bf);
    return bf;
}

char get_symbol(int x, int y)
{
    if(isNote == 1) return NOTE[y][x];
    else return TROW[x-strlen(HTOOL_MES)];
}

int end_ind(int y)
{
    int i = 0;
    while(NOTE[y][i] != 0){
        i++;
    }
    return i;
}



