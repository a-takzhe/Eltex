#include <stdio.h>
#include <stdlib.h>
#include "plug_worker.h"

void main(int argc, char* argv[])
{
   struct pw_node* pw = NULL;
   int opt, ch;
   char* message;
   int result;

   init_plug_worker(&pw, "./bin");
   print_list(pw);
   puts("\n");
      
   while(1)
   {
      //clrscr();
      puts("========================");
      printf("|0 - exit\n");
      print_operations(pw);
      printf("========================\n"
             "choose operation>> ");
  
      scanf("%d",&opt);

      if(opt == 0)
      {
         exit(1);
      }
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

