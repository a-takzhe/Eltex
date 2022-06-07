#include "memw.h"

char* insert_note(char c);
char* insert_trow(int x, char c);

char* delete_note();
char* delete_trow(int x);



void clear_nrow(int r, int c)
{
    while(NOTE[r][c] != 0)
    {
        NOTE[r][c++] = 0;
    }
}

void clear_trow()
{
    int i = 0;
    while(i<MAXCOL2)
    {
        i++;
        TROW[i]=0;
    }
}

int end_ind(int y)
{
    int i = 0;
    while(NOTE[y][i] != 0){
        i++;
    }
    return i;
}

char get_symbol(int x, int y)
{
    if(isNote == 1) return NOTE[y][x];
    else return TROW[x-strlen(HTOOL_MES)-1];
}

char get_cur_symbol()
{
    if(isNote){
        return NOTE[PN.y][PN.x];
    } 
    else{
        return ' ';
    }
}


char* insert(char c)
{
    if (isNote)
    {
        return insert_note(c);
    }
    else
    {
        //return insert_trow(x,c);
    }
    
}

char* insert_note(char c)
{
    int sl = strlen(&NOTE[PN.y][PN.x]);
    char* bf = (char*)malloc(sl+1*sizeof(char));
    
    strncpy(bf, &NOTE[PN.y][PN.x], sl+1);
    NOTE[PN.y][PN.x]=c;
    strcpy(&NOTE[PN.y][PN.x+1], bf);   

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


int mem_new_line()
{
    if(!isNote) return 0;

    int r = num_lines;
    while(r >= PN.y)
    {
        int c = 0;

        if(r != PN.y)
        {
            strcpy(NOTE[r+1], NOTE[r]);
        }
        else
        {
            strcpy(NOTE[r+1], &NOTE[r][PN.x]);
            NOTE[r][PN.x] = '\n';
            c = PN.x+1;
        }
        clear_nrow(r, c);
        r--;
    }
    num_lines++;
}




char* delete()
{
    if(isNote)
    {
        return delete_note();
    }
    else
    {
        // return delete_trow(x);
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

char* delete_note()
{
    int i = PN.x;
    int sl;
    char* bf;

    if(NOTE[PN.y][i] == '\n' && i==0)
    {

    }

    sl = strlen(&NOTE[PN.y][PN.x]);
    bf = (char*)malloc(sizeof(char)*sl+1);

    strncpy(bf, &NOTE[PN.y][PN.x], sl+1);
    NOTE[PN.y][end_ind(PN.y)] = 0;
    strcpy(&NOTE[PN.y][PN.x-1], bf);

    return bf;
}

