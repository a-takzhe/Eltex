#include <stdio.h>

char* func_name()
{
   return "add";
}

char* func_type()
{
   return "ii2i";
}

int add(int a, int b)
{
   puts("a+b");
   return  a+b;
}
