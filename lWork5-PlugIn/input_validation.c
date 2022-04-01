#include "input_validation.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define SIZE 128

void printUnsignedRange(int bytes)  
{  
    int bits = 8 * bytes;     
    unsigned long long to = (1 << (bits - 1)) + ((1 << (bits - 1)) - 1);      
    printf(" 0 to %llu\n\n", to);  
}  

void printSignedRange(int bytes)  
{  
   int bits = 8 * bytes;     
   long long from  = -(1LL << (bits - 1));  
   long long to    =  (1LL << (bits - 1)) - 1;  
   printf(" %lld to %lld\n\n", from, to);  
}  

int read_uchar(uchar* ch, char** message)
{
  int ret = 0;
  char input[SIZE];

  fgets(input, SIZE-1, stdin);
  if(sscanf(input, "%hhu", ch) != 1)
  {
    *message = "Invalid sscanf()";
    ret = -1;
  }

  if(strstr(input, "\n") == NULL)
    while ( getchar() != '\n' );
  
  return ret;
}

void validator(int* num, char sym)  
{
  char input[SIZE];

  while(1)
  {
    printf("insert number %c: ",sym);
    fgets(input, SIZE-1, stdin);

    if(sscanf(input, "%d", num) != 1)
    {
      puts("Invalid sscanf()");
      continue;
    }
    if(*num < -UCHAR_MAX || *num > UCHAR_MAX)
    {
      puts("Out of range!");
      continue;
    }
    if(strstr(input, "\n") == NULL)
      while ( getchar() != '\n' );
    break;
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
