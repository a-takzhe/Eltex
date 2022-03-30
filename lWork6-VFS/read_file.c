#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int fd;
    size_t ret;
    char buffer[1024];

    if(argc < 2)
    {
        puts("Invalid options!\nSYNOPSIS: ./read_file [FILE_NAME]");
        exit(0);
    }

    if((fd = open(argv[1], O_RDONLY)) < 0)
    {
        perror(argv[1]);
        exit(0);
    }
    printf("file(%d) is open!\n", fd);

    if((ret = read(fd, buffer, 1024)) < 0)
    {
        perror("ERROR");
        exit(0);
    }
    buffer[ret]=0;
    printf("text from file: %s\n", buffer);
    close(fd);
    return 0;
}