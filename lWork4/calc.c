double add(double a, double b)
{
   return a + b;
}

double subtract(double a, double b)
{
   return a - b;
}

double multiply(double a, double b)
{
   return a * b;
}

double divide(double a, double b)
{
   if(b == 0)
   {
      return 0;
   }
   else
   {
      return a /b;
   }
}

double factorial(double a)
{
   if(a==0) return 1;
   else return a*factorial(a-1);
}


