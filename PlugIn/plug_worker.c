#include "plug_worker.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

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

int init_plug_worker(struct pw_node *pw, char *dirname)
{
   DIR* d;
   void* handle;
   char fpath[100];
   struct dirent *dir;
   struct pw_node* _pw=pw; 
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
            _pw = add_pw_node(_pw, fpath, handle);
         }
         fpath[strlen(dirname)+1]=0;
      }
      closedir(d);
   }
}

struct pw_node* add_pw_node(struct pw_node *pw, char* fpath, void* handle)
{
   struct pw_node* current;
   if(pw == NULL)
   {
      pw = (struct pw_node*)malloc(sizeof(struct pw_node));
      if(pw == NULL)
      {
         puts("malloc error!\n");
         exit(EXIT_FAILURE);
      }
      current = pw;
      current->key = 1;
   }  
   else
   {
      current = (struct pw_node*)malloc(sizeof(struct pw_node));
      if(current == NULL)
      {
         puts("malloc error!\n");
         exit(EXIT_FAILURE);
      }
      current->key = pw->key+1;
      pw->next = current;
   }
   current->flName = fpath;
   current->fnName = exec_info_func(handle, "func_name");
   current->fnType = exec_info_func(handle, "func_type");
   current->next = NULL;

   dlclose(handle);
   return current;
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

   if(strlen(inf[0]())==0 || strlen(inf[2]())==0)
   {
      printf("error file: %s\nbad format!\n",fpath);
      dlclose(handle);
      return NULL;
   }

   return handle;
}







