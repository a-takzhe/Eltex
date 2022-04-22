#include "read_config.h"

int read_file(char* path, MENU* menu)
{
    FILE* f;
    char buffer[20];
    char *key, *func;

    if((f=fopen(path, "r")) == NULL)
    {
        return -1;
    } 
    int a = get_count_func(f, NULL);
    menu = (MENU*)malloc(sizeof(MENU)*a);
    get_count_func(f, "F1");
    get_count_func(f, "F2");
    fclose(f);
}

int get_count_func(FILE* f, char* key)
{
    int cnt = 0;
    char buffer[100];
    fseek(f, 0L, SEEK_SET);

    while ((fgets(buffer, 100, f)))
    {
        if(key == NULL && strstr(buffer, "<") != NULL)
        {
            cnt += is_comment_line(buffer);
            puts(buffer);
        }
        else if(key != NULL && strstr(buffer, ">>") != NULL && strstr(buffer, key) != NULL)
        {
            cnt += is_comment_line(buffer);
            puts(buffer);       
        }
    }
    printf("count of menu %s items: %d\n", key, cnt);
    return cnt; 
}

int is_comment_line(char* string)
{
    clean_string(string);
    if(strlen(string) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void clean_string(char* string)
{
    char *cm, *n;
    
    n = strchr(string, '\n');
    cm = strchr(string, '#');
    
    if(n!=NULL)
    {
        string[(int)(n-string)] = 0;
    }

    if(cm != NULL)
    {
        string[(int)(cm-string)] = 0;
    }
}