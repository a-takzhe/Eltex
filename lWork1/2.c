#include <stdio.h>

//Output elements of array
void ShowArr(int arr[], int N)
{
    for(int i=0; i<N; i++)
    {
        printf("%d ", arr[i]);
    }
    puts("");
}

int main(int argc, char* argv[])
{
    const int N = 11;
    int arr[N];
    int tmp;

    //fill array
    for(int i=0; i<N; i++) { arr[i]=i+1; }
 
    printf("\e[38;5;40m initial array -> "); ShowArr(arr, N);

    //reverse array
    for(int i=0; i < N/2; i++)
    {
        tmp = arr[i];
        arr[i]=arr[N-i-1];
        arr[N-i-1]=tmp;
    }

    printf("\e[38;5;51mreversed array -> "); ShowArr(arr, N);
	printf("\e[38;5;255m");
    return 0;
}



