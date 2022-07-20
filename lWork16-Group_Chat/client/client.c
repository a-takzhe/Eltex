#include <stdio.h>
#include "./lib/handler.h"

int main()
{
    srand ( time(NULL) ); 
    setlocale(LC_ALL, "");
    init();
    
    
    users[0].name = "alex"; 
    users[1].name = "tomas"; 
    users[2].name = "luke";
    users[0].active = 1; 
    users[1].active = 1; 
    users[2].active = 1;  
    update_usr_area();

    messages[0].text = "Hello friends";
    messages[1].text = "Hi";
    messages[2].text = "Hello alex";
    messages[0].u_id = 0;
    messages[1].u_id = 1;
    messages[2].u_id = 2;
    messages[3].text = "Fuck you";
    messages[3].u_id = -1;
    messages[4].text = "Fuck you too";
    messages[4].u_id = 0;

    ID_LAST_MSG = 4;
    update_msg_area();
    
    h_main();
    
    wend();

    puts("hello from client");
    return 0;
}