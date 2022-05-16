#include "rw_file.h"

// int read_file(char *path, WINDOW* wnd, char c[255][255])
// {
//     FILE* f;
//     char buffer[255];
//     int size;

//     if((f = fopen(path, "r")) == NULL)
//     {
//         return 1;
//     }

//     wmove(wnd,0,0);

//     while((size = fread(buffer, sizeof(char), 255, f)) != 0)
//     {
//         wprintw(wnd, "%s", buffer);
//     }
//     wrefresh(wnd);

//     fclose(f);
// }

int read_file(char *path, WINDOW* wnd)
{
    FILE* f;
    char buffer[255];
    int ln=0;
    int sz;

    if((f = fopen(path, "r")) == NULL)
    {
        return 1;
    }

    wmove(wnd,0,0);

    while((fgets(buffer, 255, f)) != 0)
    {
        strncpy(NOTE[ln],buffer,255);
        wprintw(wnd, "%s", buffer);
        ln++;
    }
    wrefresh(wnd);
    lln = ln;

    fclose(f);
}

int nwrite(WINDOW* wnd)
{
    int ln=0;
    while(ln<=lln)
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
