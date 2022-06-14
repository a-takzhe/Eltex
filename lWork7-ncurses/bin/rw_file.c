#include "rw_file.h"

int check_file_size(FILE *f);

int check_file_size(FILE *f)
{
    fseek(f, 0L, SEEK_END);
    long fsz = ftell(f); 
    if(fsz > MAXCOL*MAXROW)
    {
        wend();
        printf("file %s (%ldbt) is too large\n", F_NAME, fsz);
        return ERR;
    }
    fseek(f, 0L, SEEK_SET);
    return OK;
}

void clear_fname(){
    int i = 0;
    while(i < MAXCOL2){
        F_NAME[i] = 0;
        i++;
    }
}

int read_file(char *path)
{
    FILE* f;
    char buffer[MAXCOL] = {0};

    if((f = fopen(path, "r")) == NULL){
        return ERR;
    }
    if(check_file_size(f) == ERR){
        return ERR;
    }

    clear_fname();
    strcpy(F_NAME, path);

    num_lines = 0;
    clear_note();
    while((fgets(buffer, MAXCOL, f)) != 0 && num_lines < MAXROW)
    {
        strncpy(NOTE[num_lines], buffer, MAXCOL);
        num_lines++;
    }
    rewrite_mwnd(0);

    num_lines = num_lines-1 < 0 ? 0 : num_lines-1;
    fclose(f);
    
    return 1;
}

void write_fname(WINDOW* wnd)
{
    if(strlen(F_NAME) > 0 && strstr(CURMEN->func, "Save") != NULL)
    {
        wprintw(wnd, F_NAME);
        PN.x += strlen(F_NAME);
        strcpy(TROW, F_NAME);
    }
}

char* get_fname()
{
    if(strlen(TROW) !=0){
        return TROW;
    }
    else if(strlen(F_NAME) != 0){
        return F_NAME;
    }
    else{
        return "";
    }
}

int wFile()
{
    char* fname = get_fname();
    if(strlen(fname) == 0){
        return ERR;
    }
    clear_fname();
    strcpy(F_NAME, fname);

    FILE* f;
    char buffer[MAXCOL] = {0};

    if((f = fopen(fname, "w+")) == NULL){
        return ERR;
    }

    int ln = 0;
    while(ln <= num_lines)
    {
        fputs(NOTE[ln], f);
        ln++;
    }    
    fclose(f);

    return 1;
}