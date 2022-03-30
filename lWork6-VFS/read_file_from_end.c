#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int fd, i;
    size_t ret;
    char c[1];
    char buffer[1024];

    if(argc < 2)
    {
        puts("Invalid options!\nSYNOPSIS: ./read_file_from_end [FILE_NAME]");
        exit(0);
    }

    if((fd = open(argv[1], O_RDONLY)) < 0)
    {
        perror(argv[1]);
        exit(0);
    }
    printf("file(%d) is open!\n", fd);
    

    if((i=lseek(fd, 0, SEEK_END)) < 0)
    {
        perror("lseak");
    }
    printf("i: %ld\n", i);

    i = 0;
    while (1)
    {
        if(lseek(fd,-1,SEEK_CUR) < 0)
        {
            perror("lseek");
            break;
        }
        if((ret = read(fd, c, 1)) < 0)
        {
            perror("read");
            exit(0);
        }
        if(lseek(fd,-1,SEEK_CUR) < 0)
        {
            perror("lseek");
            break;
        }
        printf("%c",c[0]);
        i++;
        if(i==1024) break;
    }
    puts("");
    //printf("text from file: %s\n", buffer);
    close(fd);
    return 0;
}