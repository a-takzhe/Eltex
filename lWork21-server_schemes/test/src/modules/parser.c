#include "parser.h"

int bincheck(const char* __name__, char** token)
{
    FILE* fd;
    char *sptr;
    char *path = getenv("LW21_PATH");
    
    if(path == NULL) {
        perror("getenv");
        return -1;
    }

    while((*token = strtok_r(path, ":", &sptr)) != NULL){
        
        path = NULL;
        if(strstr(*token, __name__) != NULL){
            printf("run proc >> %s\n", *token);
            break;
        }
    }

    if((fd = fopen(*token, "r")) == NULL){
        perror(*token);
        return -1;
    }
    fclose(fd);

    return 0;
}

int parse(int argc, char** argv, char *projname, int* fork_num, char** newargw)
{
    int opt;
    int __attribute__ ((unused)) nameid; //po prikolu

    if(argc < 2){ return -1; }

    while ((opt = getopt(argc, argv, "L:l:")) != -1)
    {
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
    strcpy(projname, argv[nameid]);

    return 0;
}
