#include "read_config.h"

int read_file(char* path, struct MENU* mainMenu)
{
    FILE* f;
    char buffer[20];
    char *key, *func;

    if((f=fopen(path, "r")) == NULL)
    {
        return -1;
    } 
    get_count_func(f);
}

int get_count_func(FILE* f)
{
    int cnt = 0;
    char buffer[100];

    while ((fgets(buffer, 100, f)))
    {
        if(strstr(buffer, "<") != NULL)
        {
            if(buffer[0] == '#') continue;
            //puts(buffer);
            cnt++;
        }
    }
    //printf("count of menu items: %d\n", cnt);
    return cnt; 
}