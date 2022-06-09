#ifndef MEMW_H__
#define MEMW_H__

#include "compare.h"


u_short num_lines;
u_char isNote; 

void clear_nrow(int r, int c);
void clear_trow(int c);
char get_symbol(int x, int y);
char get_cur_symbol();
int end_ind(int y);

int mem_new_line();

char* mem_ins_sym(char c);
char* mem_del_sym();
int mem_del_row();

#endif