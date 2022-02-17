#include <stdio.h>
#include <stdlib.h>
#include "plug_worker.h"

void main(int argc, char* argv[])
{
   struct pw_node* pw = NULL;
   init_plug_worker(&pw, "./bin");
   print_list(pw);
   exit(1);
}

