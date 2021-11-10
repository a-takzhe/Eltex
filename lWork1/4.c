#include <stdio.h>

//++++++++++++++++++++++++++++
//Заполнить матрицу от 1 до N 
// в квадрате улиткой
//++++++++++++++++++++++++++++

int main(int argc, char* argv[])
{
    const int N = 5;
    int arr[N][N];
    
    int n=N; //Число элементов в строке или столбце
	int a = 1; 
	int d = N%2>0 ? 1 : 0; //добавочная единица при нечетном N

    for(int i=0; i<N/2+d; i++)
    {
		//Заполнение слева направо
        for(int j=0; j<n; j++)
        {
            arr[i][j+i]=a++;
        }
        n--;

		//Заполнение сверху вниз
        for(int j=0; j<n; j++)
        {
            arr[j+i+1][N-1-i]=a++;
        }

		//Заполнение справа налево
        for(int j=n-1; j>=0; j--)
        {
            arr[N-1-i][j+i]=a++;
        }
        n--;

		//Заполнение снизу вверх
        for(int j=n; j>0; j--)
        {
            arr[j+i][i]=a++;
        }
    }
	
	//вывод на экран
	char* c = "  ";
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
}
