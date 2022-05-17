#include "bin/handler.h"


int main(int argc, char ** argv)
{   

    if(init() == ERR)
    {
        exit(EXIT_FAILURE);
    }

    if(argc >= 2)
    {
        read_file(argv[1], __MAINWND__);
    }
    main_handler();
    wend();
    
    exit(EXIT_SUCCESS);
}