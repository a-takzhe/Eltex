#include <stdio.h>
#include "calc.h"
#include "input_validation.h"


int main(void)
{
  double a, b, c;
  int opt, ch;
  

  while(1)
  {
    clrscr();
    puts("========================");
    printf("|0 - exit\n"
           "|1 - adding numbers\n"
           "|2 - dividing numbers\n"
           "|3 - multiply numbers\n"
           "|4 - subtracts numbers\n"
           "|5 - factorial of number\n"
           "========================\n"
           "choose operation>> ");
    
    scanf("%d",&opt); 

    switch (opt)
    {
      case 1:
        bOperInput(&a, &b, "addition numbers (a+b)");
        c = add(a, b);
        printf("(%f + %f) = %f\n", a, b, c);
        break;

      case 2:
        bOperInput(&a, &b, "division numbers (a/b)");
        c = divide(a, b);
        printf("(%f \\ %f) = %f\n", a, b, c);
        break;

      case 3:
        bOperInput(&a, &b, "multiplication numbers (a*b)");
        c = multiply(a, b);
        printf("(%f * %f) = %f\n", a, b, c);
        break;

      case 4:
        bOperInput(&a, &b, "numbers subtraction (a-b)");
        c = subtract(a, b);
        printf("(%f - %f) = %f\n", a, b, c);
        break;

      case 5:
        uOperInput(&a, "factorial of number (!a)");
        c = factorial(a);
        printf("!%f = %f\n", a, c);
        break;

      case 0:
        return 0;
      
      default:
        printf("error key!\n");
        break;
    }
    
    printf("Press Enter to Continue\n");
    while((ch = getchar()) != EOF && ch != '\n');
    getchar();
  }
}

