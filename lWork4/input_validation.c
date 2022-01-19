#include "input_validation.h"
#include <stdio.h>


void validator(double* num, char sym)
{
  int e = 0;

  while(e!=1)
  {
    printf("insert number %c: ",sym);
    e = scanf("%lf", num);
    while(getchar()!='\n'){}
  }
}

void bOperInput(double* a, double* b, char* mes)
{
  clrscr();
  printf("%s\n",mes);
  puts("========================");

  validator(a, 'a');
  validator(b, 'b');
}

void uOperInput(double *a, char *mes)
{
  clrscr();
  printf("%s\n",mes);
  puts("========================");

  validator(a, 'a');
}
