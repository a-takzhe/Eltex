#include "plug_worker.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int lenght_list(struct pw_node *pw)
{
   int i = 0;
   while (pw != NULL) 
   {
      i++;
      pw=pw->next;
   }
   return i;
}

void print_list(struct pw_node *pw)
{
   while (pw != NULL) 
   {
      printf("flName: %s\n"
             "\tfnName: %s\n"
             "\tfnType: %s\n"
             "\tkey: %d\n", pw->flName, pw->fnName, pw->fnType, pw->key);
      pw=pw->next;
   }
}

struct pw_node* create_node(int oKey, char *flName, char *fnName, char *fnType)
{
   struct pw_node* pw = (struct pw_node*)malloc(sizeof(struct pw_node));
   if(pw == NULL)
   {
      puts("Allocate error!");
      return NULL;
   }
   pw->key = oKey+1;
   strcpy(pw->flName, flName);
   strcpy(pw->fnName, fnName);
   strcpy(pw->fnType, fnType);
   pw->next = NULL;

   return pw;
}

struct pw_node* insert_node(struct pw_node* pw, char* fpath, void* handle)
{

   if(pw == NULL)
   {
     return create_node(0,
                        fpath,
                        exec_info_func(handle, "func_name"),
                        exec_info_func(handle, "func_type")
                       );
   }
   else
   {
      pw->next = insert_node(pw->next, fpath, handle);
   }
   
   return pw;
}



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
            *pw = insert_node(*pw, fpath, handle);
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







