#include <stdio.h>
#include "calc.h"

#define clrscr() printf("\e[1;1H\e[2J")

void bOperation(double* a, double* b, char* oper);
void uOperation(double* a);

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
           "|5 - factorial of number\n"
           "========================\n"
           "choose operation>> ");
    
    scanf("%d",&opt); 
    
    switch (opt)
    {
      case 1:
        printf("you select adding\n");
        bOperation(&a, &b, "addition numbers (a+b)");
        c = add(a, b);
        printf("(%f + %f) = %f\n", a, b, c);
        return 0;
      default:
        printf("error key!\n");
        return 0;
    }
  }
}

void bOperation(double* a, double* b, char* oper)
{
  clrscr();
  printf("%s\n",oper);
  puts("========================");
  printf("enter number a: ");
  scanf("%lf",a);
  printf("enter number b: ");
  scanf("%lf",b);
}

