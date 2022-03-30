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
            char* fn = exec_info_func(handle, "func_name");
            char* ft = exec_info_func(handle, "func_type");

            *pw = insert_node(*pw, fpath, fn, ft, lenght_list(*pw));
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
   char* ff = inf();
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

void print_operations(struct pw_node *pw)
{
   while (pw != NULL) 
   {
      printf("|%d - %s\n", pw->key, pw->fnName);
      pw=pw->next;
   }
}

char* exec_function(struct pw_node *pw, int num, int* result)
{
   int a, b;
   void *handle;
   char *error;
   struct pw_node* s_pw = get_node_by_key(pw, num);
   
   if(s_pw == NULL)
   {
      return "BAD KEY";
   }
   else
   {
      handle = dlopen(s_pw->flName, RTLD_LAZY);
      if (!handle) 
      {
         fprintf(stderr, "%s\n", dlerror());
         return "HANDLE";
      }
      dlerror();

      if(strstr(s_pw->fnType, "ii2i"))
      {
         bOperInput(&a, &b, "input two numbers");
         ii_2_i = dlsym(handle, s_pw->fnName);
         
         error = dlerror();
   
         if (error != NULL) 
         {
            fprintf(stderr, "%s\n", error);
            dlclose(handle);
            return error;
         }
         *result = (*ii_2_i)(a, b);
         return "OK";
      }
      else
      {
         uOperInput(&a,"input one number");

         i_2_i = dlsym(handle, s_pw->fnName);
         
         error = dlerror();
   
         if (error != NULL) 
         {
            fprintf(stderr, "%s\n", error);
            dlclose(handle);
            return error;
         }
         *result = (*i_2_i)(a);
         return "OK";
      }
   }
}

