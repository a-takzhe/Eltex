#include "pw_list.h"
#include <dirent.h>
#include <stdlib.h>
#include <dlfcn.h>


/*check plugin config. fpath - path to .so file*/
void* is_plugin(char* fpath);
char* exec_info_func(void* handle, char* fnName);
int init_plug_worker(struct pw_node **pw, char* dirname);

typedef char* (*_info_)();
int (*i_2_i)(int);
int (*ii_2_i)(int,int);
float (*ii_2_f)(int,int);

