#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "plug_worker.h"

#define DEBUG

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


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

void main(int argc, char* argv[])
{
   struct pw_node* pw = NULL;
   uchar opt, ch;
   char* message;
   int result;

   init_plug_worker(&pw, "./bin");
#ifdef DEBUG  
   print_list(pw); puts("\n");
#endif

   while(1)
   {
#ifndef DEBUG
      clrscr();
#endif
      puts("========================");
      puts("|0 - exit");
      print_operations(pw);
      printf("========================\nchoose operation>> ");
  
      if(read_uchar(&opt) == -1){ continue; }
      if(opt == 0) { exit(1); }
      else
      {
         message = exec_function(pw, opt, &result);
         if(strstr(message, "OK"))
         {
            printf("result: %d\n", result);
         }
         else
         {
            printf("ERROR %s!\n", message);
         }
      }

      printf("Press Enter to Continue\n");
      while((ch = getchar()) != EOF && ch != '\n');
      getchar();
   }

   exit(1);
}

