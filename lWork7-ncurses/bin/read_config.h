#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MENU
{
    char* key;
    char* func;
    ushort isUseSubstr;
    struct MENU* subMenu;
};

int read_file(char* path, struct MENU* mainMenu);
int get_count_func(FILE* f);
