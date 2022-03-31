#include "input_validation.h"
#include <stdio.h>
#include <limits.h>

int read_uchar(uchar* ch)
{
  int SIZE = 100, ret = 0;
  char input[SIZE];

  fgets(input, SIZE-1, stdin);
  if(sscanf(input, "%hhu", ch) != 1)
  {
    puts("Invalid sscanf()");
    ret = -1;
  }
  while ( getchar() != '\n' );
  return ret;
}

void validator(int* num, char sym)
{
  int e = 0, ch;

  while(e!=1)
  {
    printf("insert number %c: ",sym);
    e = scanf("%d", num);
    if(e == 1) break;
    while((ch = getchar()) != EOF && ch != '\n');
  }
}

void bOperInput(int* a, int* b, char* mes)
{
  clrscr();
  printf("%s\n",mes);
  puts("========================");

  validator(a, 'a');
  validator(b, 'b');
}

void uOperInput(int *a, char *mes)
{
  clrscr();
  printf("%s\n",mes);
  puts("========================");

  validator(a, 'a');
}
