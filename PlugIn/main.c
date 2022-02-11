#include <stdio.h>
#include <stdlib.h>
#include "plug_worker.h"

void main(int argc, char* argv[])
{
   struct pw_node* pw = NULL;
   print_list(pw);
   init_plug_worker(pw, "./bin");
   exit(1);
}

