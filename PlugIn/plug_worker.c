#include "plug_worker.h"



int init_plug_worker(struct pw_node **pw, char *dirname)
{
   DIR* d;
   void* handle;
   char fpath[100];
   struct dirent *dir;
   d = opendir(dirname);

   if(d)
   {
      strcpy(fpath, dirname);
      strcat(fpath, "/");

      while((dir = readdir(d)) != NULL)
      {
         strcat(fpath, dir->d_name);
         if(strstr(fpath,".so") && (handle = is_plugin(fpath)) != NULL)
         {
            *pw = insert_node(*pw, fpath, 
                               exec_info_func(handle, "func_name"),
                               exec_info_func(handle, "func_name"),
                               lenght_list(*pw)
                              );
            dlclose(handle);
         }
         fpath[strlen(dirname)+1]=0;
      }
      closedir(d);
   }
}


char* exec_info_func(void* handle, char* fnName)
{
   _info_ inf;
   inf = dlsym(handle, fnName);
   
   char* error = dlerror();
   
   if (error != NULL) 
   {
      fprintf(stderr, "%s\n", error);
      dlclose(handle);
      return NULL;
   }
   return inf();
}

void* is_plugin(char *fpath)
{
   void *handle;
   char *error;
   _info_ inf[2];

   handle = dlopen(fpath, RTLD_LAZY);
   if (!handle) 
   {
      fprintf(stderr, "%s\n", dlerror());
      return NULL;
   }
   
   dlerror();

   inf[0]= dlsym(handle, "func_name");
   inf[1]= dlsym(handle, "func_type");
   
   error = dlerror();
   
   if (error != NULL) 
   {
      fprintf(stderr, "%s\n", error);
      dlclose(handle);
      return NULL;
   }

   return handle;
}







