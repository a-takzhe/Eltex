#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct pw_node
{
   int key;
   char flName[100];
   char fnName[30];
   char fnType[10];
   struct pw_node* next;
};

int lenght_list(struct pw_node *pw);
struct pw_node* insert_node(struct pw_node* pw, char* fpath, void* handle);
struct pw_node* create_node(int oKey, char* flName, char* FnName, char* fnType);
void print_list(struct pw_node* pw);

/*check plugin config. fpath - path to .so file*/
void* is_plugin(char* fpath);
char* exec_info_func(void* handle, char* fnName);
int init_plug_worker(struct pw_node **pw, char* dirname);

typedef char* (*_info_)();
int (*i_2_i)(int);
int (*ii_2_i)(int,int);
float (*ii_2_f)(int,int);

