#include <stdio.h>

int main(int argc, char* argv[])
{
    int N;
    printf("Please enter the N: ");
    scanf("%d", &N);
    
    for(int i=0; i<N; i++)
    {
        for(int j=i*N; j<i*N+N; j++)
        {
            printf("%d ", j+1);
        }
        printf("\n");
    }
	
    return 0;
}
