#include <stdio.h>

char* func_name()
{
   return "multiply";
}

char* func_type()
{
   return "ii2i";
}

int multiply(int a, int b)
{
   puts("a*b");
   return  a*b;
}
