#include <stdio.h>

char* func_name()
{
   return "factorial";
}

char* func_type()
{
   return "i2i";
}

int factorial(int a)
{
   if(a==0)
   {
      puts("a!");
      return 1;
   } 
   else return a*factorial(a-1);
}