#include "pw_list.h"

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

struct pw_node* insert_node(struct pw_node* pw, char* fpath, char* fnName, char* fnType, int key)
{

   if(pw == NULL)
   {
     return create_node(key,
                        fpath,
                        fnName,
                        fnType
                       );
   }
   else
   {
      pw->next = insert_node(pw->next, fpath, fnName, fnType, key);
   }
   
   return pw;
}