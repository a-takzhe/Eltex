#include <stdio.h>

int main(int argc, char* argv[])
{
    const int N = 5;
    int arr[N][N];
    
    int n=N;
    int a = 1;
	char* c = "  ";
	int added = N%2>0 ? 1 : 0;	

    for(int i=0; i<N/2+added; i++)
    {
		//left to right
        for(int j=0; j<n; j++)
        {
            arr[i][j+i]=a++;
        }
        n--;
		//top to bottom
        for(int j=0; j<n; j++)
        {
            arr[j+i+1][N-1-i]=a++;
        }
		//right to left
        for(int j=n-1; j>=0; j--)
        {
            arr[N-1-i][j+i]=a++;
        }
        n--;
		//bottom to top
        for(int j=n; j>0; j--)
        {
            arr[j+i][i]=a++;
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
			if(arr[i][j] > 9){c = " ";}
			if(arr[i][j] < 10){c="  ";}
           
			 printf("%d", arr[i][j]);
			printf("%s", c);
		}
        puts("");
    }

    
    return 0;
}
