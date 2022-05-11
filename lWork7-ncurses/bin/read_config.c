#include "read_config.h"

//+++++++++++++++++++++++++++++++++++++
//prototype function
//+++++++++++++++++++++++++++++++++++++
int is_comment_line(char* string);
void fill_menu(MENU** menu, FILE* f);
void fill_subMenu(MENU** menu, FILE* f);
void create_menu_node(MENU** menu, char* string, int isSubM);


//+++++++++++++++++++++++++++++++++++++
//function implementation
//+++++++++++++++++++++++++++++++++++++
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

int init_menu(MENU** menu)
{
    FILE* f;
    int count=0;

    if((f=fopen(PATH_CONFIG, "r")) == NULL) return -1;

    fill_menu(menu, f);
    fclose(f);
    
    return 1;
}

void fill_menu(MENU** menu, FILE* f)
{
    char buffer[100];

    while ((fgets(buffer, 100, f)))
    {
        clean_string(buffer);
        // printf("f - %s\n", buffer);

        if(strstr(buffer, "<") != NULL)
        {
            create_menu_node(menu, buffer, 0);
            fill_subMenu(&(*menu)->subMenu, f);
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
        // printf("\tsf - %s\n", buffer);

        if(strstr(buffer, ">>") != NULL)
        {
            create_menu_node(menu, buffer, 1);
            fill_subMenu(&(*menu)->nextFunc, f);
            return;
        }
        if(strstr(buffer, "<") != NULL)
        {
            fseek(f, -len, SEEK_CUR);
            // puts("seek back");
            return;
        }
    }
}

void create_menu_node(MENU** menu, char* string, int isSubM)
{
    *menu = (MENU*)malloc(sizeof(MENU));
    char *k, *f;
    k = strtok(string, ":");
    f = strtok(NULL, ":");
    sscanf(strtok(NULL, ":"), "%o", &(*menu)->key); 

    if(isSubM == 0){
        strcpy((*menu)->key_name, k+1);
        sscanf(strtok(NULL, ":"), "%hd", &(*menu)->isUseSubstr);
    }
    else{
        strcpy((*menu)->key_name, k+2);
    }
    strcpy((*menu)->func, f);

    (*menu)->key_name[2]=0;
    (*menu)->func[strlen(f)]=0;

}

void show_menu(MENU* menu, int isSub)
{
    if(menu == NULL) return;
    if(isSub){
        printf("  key_n:%s, func:%s, key:%04o\n", menu->key_name, menu->func, menu->key);
    }
    else{
        printf("key_n:%s, func:%s, key:%04o, use:%hd\n", menu->key_name, menu->func, 
                menu->key, menu->isUseSubstr);
    }
    show_menu(menu->subMenu, 1);
    show_menu(menu->nextFunc, isSub);
}

MENU* get_menu_by_key(int key, MENU* menu)
{
    while (menu != NULL && menu->key != key)
    {
        menu = menu->nextFunc;
    }    
    return menu;
}







