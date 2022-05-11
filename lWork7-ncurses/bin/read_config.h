#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH_CONFIG "./configure/cmd.config"

struct t_menu
{
    struct t_menu* subMenu;
    struct t_menu* nextFunc;
    int key;
    ushort isUseSubstr;
    char func[20];
    char key_name[3];
};
typedef struct t_menu MENU; 

int init_menu(MENU** menu);
void show_menu(MENU* menu, int isSub);
MENU* get_menu_by_key(int key, MENU* menu);

