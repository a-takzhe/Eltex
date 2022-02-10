#include <stdio.h>
#include <stdlib.h>
#include "plug_worker.h"

void main(int argc, char* argv[])
{
   struct PlugConf* pf;
   int cnt = 0;
   
   cnt=pCnt("./bin");
   printf("libs count: %d\n", cnt);

   pf = (struct PlugConf*)malloc(sizeof(struct PlugConf)*cnt);
   
   if(pf == NULL)
   {
      puts("malloc error!\n");
      return;
   }
   
   exit(1);
}

