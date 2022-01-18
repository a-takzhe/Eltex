#include <stdio.h>
#include "calc.h"

#define clrscr() printf("\e[1;1H\e[2J")

int main(void)
{
  double a, b, c;
  int opt;

  while(1)
  {
    clrscr();
    puts("========================");
    printf("|1 - adding numbers\n"
           "|2 - dividing numbers\n"
           "|3 - multiply numbers\n"
           "|4 - subtracts numbers\n"
           "========================\n"
           "choose operation>> ");
    
    scanf("%d",&opt); 
    
    switch (opt)
    {
      case 1:
        printf("you select adding\n");
        return 0;
      default:
        printf("error key!\n");
        return 0;
    }
  }

  //c = add(a,b);
  //printf("c = %f\n",c);
}

