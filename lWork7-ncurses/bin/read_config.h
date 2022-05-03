#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMDWND_CONFIG "./configure/cmd.config"

struct t_menu
{
    struct t_menu* subMenu;
    struct t_menu* nextFunc;
    int ukey;
    ushort isUseSubstr;
    char func[20];
    char key[3];
};
typedef struct t_menu MENU; 

int init_menu(MENU** menu);
int get_count_func(FILE* f, char* key);
void clean_string(char* string);
int is_comment_line(char* string);
void fill_menu(MENU** menu, FILE* f);
void fill_subMenu(MENU** menu, FILE* f);
void create_menu_node(MENU** menu, char* string, int isSubM);
void show_menu(MENU* menu, int isSub);

