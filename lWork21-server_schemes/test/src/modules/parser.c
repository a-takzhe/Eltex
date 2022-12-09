#include "parser.h"

int bincheck(const char* __name__)
{
    char path[256]={0};
    if (getcwd(path, sizeof(path)) != NULL) {
       printf("Current working dir: %s\n", path);
    }

    strcpy(path, "../../");
    strcat(path, __name__);
    strcat(path, "/client/bin/client.out");

    if(fopen("testApp", "w") == NULL){
        perror(path);
        return -1;
    }

    printf("run proc >> %s\n", path);   
    return 0;
}

int parse(int argc, char** argv, char *appName, int* fork_num, char** newargw)
{
    int opt;
    int __attribute__ ((unused)) nameid; //po prikolu

    if(argc < 2){ return -1; }

    while ((opt = getopt(argc, argv, "L:l:")) != -1)
    {
        //printf("ind: (%d) opt: (%c) optarg: (%s)\n", optind, opt, optarg);

        switch (opt)
        {
            case 'l':
            case 'L':
                *fork_num = atoi(optarg);
                break;

            default:
                break;
        }
    }
    if(*fork_num == 0) *fork_num = 1;
    
    if(optind < argc-1){
        printf("Error param: %s\n", argv[optind]);
        return -1;
    }
    
    nameid = optind == argc ? argc-1 : optind;
    strcpy(appName, argv[nameid]);

    return 0;
}
