#include <stdio.h>

int main(int argc, char* argv[])
{
    int N, tmp, e;
    
    do
    {
        printf("Enter the N: ");
        e = scanf(" %d", &N);
        while(getchar()!='\n'){}
    }
    while(e!=1);
    
    puts("========================");
    
    do
    {
        printf("1)Top triangle of zeros\n");
        printf("2)Bottom triangle of zeros\n");
        printf("Choose an option:");
        e = scanf("%d", &tmp);
        while(getchar()!='\n'){}
    }
    while(e!=1);
   
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(tmp == 1)
            {
                if(j<N-i){printf("0 ");}
                else{printf("1 ");}
            }
            else
            {
                if(j<N-i){printf("1 ");}
                else{printf("0 ");}
            }
        }
        puts("");
    }
    
    return 0;
}
