#include <stdio.h>

char* func_name()
{
   return "divide";
}

char* func_type()
{
   return "ii2i";
}

int divide(int a, int b)
{
    if(b == 0)
    {
        return 0;
    }
    else
    {
        return  a/b;
    }
}
