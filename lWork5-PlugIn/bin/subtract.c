#include <stdio.h>

char* func_name();
char* func_type();
int subtract(int a, int b);

char* func_name()
{
   return "subtract";
}

char* func_type()
{
   return "ii2i";
}

int subtract(int a, int b)
{
   puts("a-b");
   return  a-b;
}
