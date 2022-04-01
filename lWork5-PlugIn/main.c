#include <stdio.h>
#include <stdlib.h>
#include "plug_worker.h"

//#define DEBUG

void main(int argc, char* argv[])
{
   struct pw_node* pw = NULL;
   uchar opt, ch;
   char* message = "success";
   int result;

   init_plug_worker(&pw, "./bin");
#ifdef DEBUG  
   print_list(pw);
#endif

   while(1)
   {
      clrscr();
      puts(message);
      puts("========================");
      puts("|0 - exit");
      print_operations(pw);
      printf("========================\nchoose operation>> ");
  
      if(read_uchar(&opt, &message) == -1)
      { 
         continue; 
      }
      if(opt == 0) 
      { 
         exit(1); 
      }
      else
      {
         message = exec_function(pw, opt, &result);
         if(strstr(message, "OK") == NULL)
         {
            continue;
         }
         
         printf("result: %d\n", result);
         printf("Press Enter to Continue\n");
         while((ch = getchar()) != EOF && ch != '\n');
      }
   }
   exit(1);
}

