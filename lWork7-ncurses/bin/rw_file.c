#include "rw_file.h"

char* insert_note(int x, int y, char c);
char* insert_trow(int x, char c);

char* delete_note(int x, int y);
char* delete_trow(int x);


int read_file(char *path, WINDOW* wnd)
{
    FILE* f;
    char buffer[MAXCOL] = {0};
    int ln=0;
    int sz;

    if((f = fopen(path, "r")) == NULL)
    {
        return -1;
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

char* insert(int x, int y, char c)
{
    if (isNote)
    {
        return insert_note(x,y,c);
    }
    else
    {
        return insert_trow(x,c);
    }
    
}

char* insert_note(int x, int y, char c)
{
    if(NOTE[y][x] == 0)
    {
        NOTE[y][x] = c;
        return "";
    }

    int sl = strlen(&NOTE[y][x]);
    char* bf = (char*)malloc(sl+1*sizeof(char));
    
    strncpy(bf, &NOTE[y][x], sl+1);
    NOTE[y][x]=c;
    strcpy(&NOTE[y][++x], bf);   

    return bf;
}

char* insert_trow(int x, char c)
{
    x  -= strlen(HTOOL_MES);
    if(TROW[x] == 0)
    {
        TROW[x] = c;
        return "";
    }

    int sl = strlen(&TROW[x]);
    char* bf = (char*)malloc(sl*sizeof(char));
    
    strncpy(bf, &TROW[x], sl+1);
    TROW[x] = c;
    strcpy(&TROW[++x], bf);

    return bf;
}

char* delete(int x, int y)
{
    if(isNote)
    {
        return delete_note(x, y);
    }
    else
    {
        return delete_trow(x);
    }
}

char* delete_trow(int x)
{
    int i = x-strlen(HTOOL_MES)-1;
    int sl = strlen(&TROW[x]);
    char* bf = (char*)malloc(sizeof(char)*sl+1);
    strncpy(bf, &TROW[x], sl+1);

    while(TROW[i] != 0)
    {
        TROW[i] = 0;
        i++;
    }
    strcpy(&TROW[--x], bf);
    return bf;
}

char* delete_note(int x, int y)
{
    // int i = x;
    // int sl = strlen(&NOTE[y][x]);
    // char* bf = (char*)malloc(sizeof(char)*sl+1);
    // strncpy(bf, &NOTE[y][x], sl+1);

    // while(NOTE[y][i] != 0){
    //     NOTE[y][i] = 0;
    //     i++;
    // }
    // strcpy(&NOTE[y][--x], bf);
    // return bf;
    return "";
}

char get_symbol(int x, int y)
{
    if(isNote == 1) return NOTE[y][x];
    else return TROW[x-strlen(HTOOL_MES)-1];
}

int end_ind(int y)
{
    int i = 0;
    while(NOTE[y][i] != 0){
        i++;
    }
    return i;
}

void clear_trow()
{
    int i = 0;
    while(i<MAXCOL2){
        i++;
        TROW[i]=0;
    }
}

