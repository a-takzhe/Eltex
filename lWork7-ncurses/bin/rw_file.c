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

int read_file(char *path)
{
    FILE* f;
    char buffer[MAXCOL] = {0};

    char* fname = rindex(path, '/');
    if(fname == NULL){
        strcpy(F_NAME, path);
    }
    else{
        strcpy(F_NAME, ++fname);
    }

    if((f = fopen(path, "r")) == NULL){
        return ERR;
    }
    if(check_file_size(f) == ERR){
        return ERR;
    }

    num_lines = 0;
    while((fgets(buffer, MAXCOL, f)) != 0 && num_lines < MAXROW)
    {
        clear_nrow(num_lines, 0);
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
    if(strlen(F_NAME) > 0)
    {
        wprintw(wnd, F_NAME);
        PN.x += strlen(F_NAME);
        strcpy(TROW, F_NAME);
    }
}

