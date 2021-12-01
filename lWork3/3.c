#include    <stdio.h>
#include    <stdlib.h>
#include    <fcntl.h>
#include    <sys/types.h>
#include    <sys/stat.h>
    
int main ( int argc, char *argv[] )
{
        int fd;
    if((fd=open("temp",O_WRONLY,0777))<0)
    {
        perror("File");
        exit(1);
    }
    printf ( "No of Characters Written:%d\n", write(fd,"\0\0\0\0\0\0\0\0",1) );
    return 0;
}
