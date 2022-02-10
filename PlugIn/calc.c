#include <pthread.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

struct PlugConf
{
   char* flName;
   char* fnName;
   char* fnType;
};

int cntplg(char* dirname)
{

   struct dirent *dir;
   DIR* d;
   int cnt;
   d = opendir(dirname);

   if(d)
   {
      while((dir = readdir(d)) != NULL)
      {
         if(strstr(dir->d_name,"txt"))
         {
            cnt+=1;
            printf("%s-%d\n", dir->d_name, dir->d_type);
         }
      }
      closedir(d);
   }
   return cnt;
} 

int main(void)
{
   struct PlugConf* pConfArr;  
   int pCnt;

   pCnt = cntplg("bin");
   
   pConfArr = (struct PlugConf*)malloc(sizeof(struct PlugConf)*pCnt);
   if(pConfArr == NULL)
   {
      puts("malloc error!\n");
      exit(1);
   }

   for(int i=0; i<pCnt; i++)
   {
      pConfArr[i].flName="1.txt";
   }

   return 0;
}





