#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct PlugCNFG
{
    char* flName;
    char* fnName;
    char* fnType;
};

int main(void)
{
    //PlugCNFG Pconf[10];
    struct dirent *dir;
    int f_count;
    DIR *d;
    
    d=opendir("./bin");

    if(d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name, ".txt"))
            {
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
    }

    return 0;
}


