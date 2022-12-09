#include "parser.h"

int parse(int argc, char** argv, char *appName, int* fork_num, char** newargw)
{
    int opt;

    if(argc < 2){ return -1; }

    while ((opt = getopt(argc, argv, "L:")) != -1)
    {
        printf("opt: (%c) optarg: (%s)\n", opt, optarg);

        switch (opt)
        {
            case 'L':
                *fork_num = atoi(optarg);
                break;

            default:
                break;
        }
    }

    strcpy(appName, argv[argc-1]);

    return 0;
}
