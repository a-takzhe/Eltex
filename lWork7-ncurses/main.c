#include "bin/handler.h"


int main(int argc, char ** argv)
{   
    if(init() == ERR)
    {
        exit(EXIT_FAILURE);
    }
    if(argc >= 2)
    {
        if(read_file(argv[1]) == ERR)
        {
            exit(EXIT_FAILURE);
        }
    }
    else{
        init_emp_note();
    }
    main_handler();
    wend();
    
    exit(EXIT_SUCCESS);
}