#include "read_config.h"

int read_file(char* path, MENU** menu)
{
    FILE* f;
    int count=0;

    if((f=fopen(path, "r")) == NULL)
    {
        return -1;
    } 
    
    //menu = (MENU*)malloc(sizeof(MENU));


    fill_menu(menu, f);
    // get_count_func(f, "F1");
    // get_count_func(f, "F2");

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

void fill_menu(MENU** menu, FILE* f)
{
    char buffer[100];

    while ((fgets(buffer, 100, f)))
    {
        clean_string(buffer);
        printf("f - %s\n", buffer);

        if(strstr(buffer, "<") != NULL)
        {
            create_menu_node(&menu, buffer, 0);
            // fill_subMenu(NULL, f);
            fill_menu(&(*menu)->nextFunc, f);
            return;
        }
    }
}

void fill_subMenu(MENU** menu, FILE* f)
{
    char buffer[100];
    int len;

    while ((fgets(buffer, 100, f)))
    {
        len = strlen(buffer);
        clean_string(buffer);
        printf("\tsf - %s\n", buffer);

        if(strstr(buffer, ">>") != NULL)
        {
            // create_menu_node
            fill_subMenu(menu, f);
            return;
        }
        if(strstr(buffer, "<") != NULL)
        {
            fseek(f, -len, SEEK_CUR);
            puts("seek back");
            return;
        }
    }
}

void create_menu_node(MENU*** menu, char* string, int isSubM)
{
    **menu = (MENU*)malloc(sizeof(MENU));
    printf("create menu: %s\n", string);
    char *k, *f;
    k = strtok(string, ":");
    f = strtok(NULL, ":");

    strcpy((**menu)->key, k);
    // (**menu)->key[2]=0;
    strcpy((**menu)->func, f);
    (**menu)->func[strlen(f)]=0;

    sscanf(strtok(NULL, ":"), "%hd", &(**menu)->isUseSubstr);
}

void show_menu(MENU* menu, int isSub)
{
    if(menu == NULL) return;
    if(isSub){
        printf("   key:%s,func:%s\n", menu->key, menu->func);
    }
    else{
        printf(" key:%s, func:%s, use:%hd\n", menu->key, menu->func, menu->isUseSubstr);
    }
    show_menu(menu->subMenu, 1);
    show_menu(menu->nextFunc, 0);
}








