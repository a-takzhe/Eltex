#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct t_menu
{
    char* key;
    char* func;
    ushort isUseSubstr;
    struct t_menu* subMenu;
};
typedef struct t_menu MENU; 

int read_file(char* path, MENU* menu);
int get_count_func(FILE* f, char* key);
void clean_string(char* string);
int is_comment_line(char* string);