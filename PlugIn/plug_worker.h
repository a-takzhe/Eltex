#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct PlugConf
{
   char* flName;
   char* fnName;
   char* fnType;
};

int pCnt(char* dirname);
int isPlug(char* fPath);
void pConfFill(struct PlugConf* pf);

char* (*_info_)();
int (*i_2_i)(int);
int (*ii_2_i)(int,int);
float (*ii_2_f)(int,int);

