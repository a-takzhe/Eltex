#include "memw.h"

char* ins_note_sym(char c);
char* ins_trow_sym(char c);

char* del_note_sym();
char* del_trow_sym();
int mem_del_row();
int move_lines_up();



void clear_nrow(int r, int c)
{
    while(NOTE[r][c] != 0)
    {
        NOTE[r][c++] = 0;
    }
}

void clear_trow(int c)
{
    while(c < MAXCOL2)
    {
        TROW[c++]=0;
    }
}

int end_ind(int y)
{
    int i = 0;
    if(isNote)
    {
        while (NOTE[y][i] != 0)
        {
            i++;
        }
    }
    else
    {
        while (TROW[i] != 0)
        {
            i++;
        } 
    } 
    return --i;
}

char get_symbol(int x, int y)
{
    if(isNote == 1) return NOTE[y][x];
    else return TROW[x-strlen(HTOOL_MES)];
}

char get_cur_symbol()
{
    if(isNote){
        return NOTE[PN.y][PN.x];
    } 
    else{
        return TROW[PN.x-strlen(HTOOL_MES)] == 0 ? '_' : TROW[PN.x-strlen(HTOOL_MES)];
    }
}



char* mem_ins_sym(char c)
{
    if (isNote)
    {
        return ins_note_sym(c);
    }
    else
    {
        return ins_trow_sym(c);
    }
    
}

char* ins_note_sym(char c)
{
    int sl = strlen(&NOTE[PN.y][PN.x]);
    char* bf = (char*)malloc((sl+1)*sizeof(char));
    
    strncpy(bf, &NOTE[PN.y][PN.x], sl+1);
    NOTE[PN.y][PN.x]=c;
    strcpy(&NOTE[PN.y][PN.x+1], bf);   

    return bf;
}

char* ins_trow_sym(char c)
{
    int x  = PN.x - strlen(HTOOL_MES);
    int sl = strlen(&TROW[x]);
    char* bf = (char*)malloc(sl*sizeof(char));
    
    strncpy(bf, &TROW[x], sl+1);
    TROW[x] = c;
    strcpy(&TROW[x+1], bf);

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



char* mem_del_sym()
{
    if(isNote)
    {
        return del_note_sym();
    }
    else
    {
        return del_trow_sym();
    }
}

char* del_note_sym()
{
    int sl = strlen(&NOTE[PN.y][PN.x]);
    char* bf = (char*)malloc(sizeof(char)*(sl+1));

    strncpy(bf, &NOTE[PN.y][PN.x], sl+1);
    NOTE[PN.y][end_ind(PN.y)] = 0;
    strcpy(&NOTE[PN.y][PN.x-1], bf);

    return bf;
}

char* del_trow_sym()
{
    int x = PN.x-strlen(HTOOL_MES);
    int sl = strlen(&TROW[x]);
    char* bf = (char*)calloc(sl+1, sizeof(char));
    
    strncpy(bf, &TROW[x], sl+1);
    TROW[end_ind(0)] = 0;
    strcpy(&TROW[x-1], bf);
    return bf;
}

int mem_del_row()
{
    if(strlen(NOTE[PN.y-1]) + strlen(NOTE[PN.y]) - 2 < MAXCOL-2)
    {
        int x = end_ind(PN.y-1);
        strcpy(&NOTE[PN.y-1][x], NOTE[PN.y]);
        move_lines_up(); 

        return x;
    }
    else
    {
        return -1;
    }
}

int move_lines_up()
{
    int r = PN.y;
    int c = 0;
    clear_nrow(r, 0);
    while(strlen(NOTE[r+1]) != 0)
    {
        strcpy(NOTE[r], NOTE[r+1]);
        r++;
        clear_nrow(r, 0);
    }
    num_lines--;
}

