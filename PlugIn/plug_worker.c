#include "plug_worker.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>


int pCnt(char* dirname)
{
   struct dirent *dir;
   char fpath[100];
   DIR* d;
   int cnt;
   d = opendir(dirname);
   
   if(d)
   {
      strcpy(fpath, dirname);
      strcat(fpath, "/");

      while((dir = readdir(d)) != NULL)
      {
         strcat(fpath, dir->d_name);
         if(strstr(dir->d_name,"so") && isPlug(fpath))
         {
            cnt+=1;
         }
         fpath[strlen(dirname)+1]=0;
      }
      closedir(d);
   }

   return cnt;
} 


int isPlug(char *fPath)
{
   void *handle;
   char *error;

   handle = dlopen(fPath, RTLD_LAZY);
   if (!handle) 
   {
      fprintf(stderr, "%s\n", dlerror());
      return 0;
   }
   dlerror();

   printf("fln:%s  fnn:", fPath);

   _info_=dlsym(handle, "func_name");
   
   error = dlerror();
   if (error != NULL) 
   {
      fprintf(stderr, "%s\n", error);
      return 0;
   }

   printf("%s\n", _info_());
   dlclose(handle);
   return 1;
}







