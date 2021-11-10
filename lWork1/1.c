#include <stdio.h>

//+++++++++++++++++++++++
// Вывести квадратную 
// матрицу по заданному N
//+++++++++++++++++++++++

int main(int argc, char* argv[])
{
    int N, e;

	//Считывание числа N
	do
    {
        printf("Введите число элементов массива: ");
        e = scanf("%d", &N);
        while(getchar()!='\n'){}
    }
    while(e!=1); 
    
	//Вывод
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
