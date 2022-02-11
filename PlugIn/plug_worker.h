#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct pw_node
{
   int key;
   char* flName;
   char* fnName;
   char* fnType;
   struct pw_node* next;
};

struct pw_node* add_pw_node(struct pw_node* pw, char* fpath, void* handle);

int init_plug_worker(struct pw_node* pw, char* dirname);
char* exec_info_func(void* handle, char* fnName);
int plug_count(char* dirname);
void* is_plugin(char* fPath);
void print_list(struct pw_node* pw);

typedef char* (*_info_)();
int (*i_2_i)(int);
int (*ii_2_i)(int,int);
float (*ii_2_f)(int,int);

