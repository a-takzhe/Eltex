#include "pw_list.h"
#include "input_validation.h"
#include <stdio.h>
#include <dirent.h>
#include <dlfcn.h>


/*check plugin config. fpath - path to .so file*/
void* is_plugin(char* fpath);
char* exec_info_func(void* handle, char* fnName);
int init_plug_worker(struct pw_node **pw, char* dirname);
void print_operations(struct pw_node *pw);
char* exec_function(struct pw_node *pw, int num, int* result);

typedef char* (*_info_)();
int (*i_2_i)(int);
int (*ii_2_i)(int,int);
float (*ii_2_f)(int,int);

