#include <stdio.h>

int main(int argc, char* argv[])
{
    int N = 5;
    int arr[N][N];
    
    int n=N;
    int a = 1;

    for(int i=0; i<N/2; i++)
    {
        for(int j=i; j<n+i; j++)
        {
            arr[i][j]=a++;
        }
        n--;
        for(int j=i+1; j<N; j++)
        {
            arr[j][N-1-i]=a++;
        }
        if(a>16){break;}
        for(int j=n-1; j>=i; j--)
        {
            arr[n-i][j]=a++;
        }
        n--;
        for(int j=n; j>=i+1; j--)
        {
            arr[j][i]=a++;
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%d ", arr[i][j]);
        }
        puts("");
    }

    
    return 0;
}
