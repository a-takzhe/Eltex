#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int fd;
    size_t ret;

    if(argc < 3)
    {
        puts("Invalid options!\nSYNOPSIS: ./write_file [FILE_NAME] [STRING]");
        exit(0);
    }

    if((fd = open(argv[1], O_CREAT | O_WRONLY, S_IRWXU)) < 0)
    {
        perror(argv[1]);
        exit(0);
    }
    printf("file(%d) is open/created!\n", fd);

    if((ret = write(fd, argv[2], strlen(argv[2]))) < 0)
    {
        perror("ERROR");
        exit(0);
    }
    puts("File written!");
    close(fd);
    return 0;
}