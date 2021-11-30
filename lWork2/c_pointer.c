#include <stdio.h>

#define uchar unsigned char

int test(int a)
{
   int b = 0;
   retutn b+a;
}

int main(void)
{
    int a = 25963548;
    uchar c = 255;
    uchar d = 254;
    uchar e = 253;
    uchar f = 252;
    uchar* ptr = (uchar*)&a;

    a = test(a);

    printf("1 -> %x\n", *ptr);
    ptr++;
    
    printf("2 -> %x\n", *ptr);
    ptr++;
    
    printf("3 -> %x\n", *ptr);
    ptr++;
    
    printf("4 -> %x\n", *ptr);
    ptr++;
 
    printf("5 -> %x\n", *ptr);

    printf("char c = %x\n", c);
}

