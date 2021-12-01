#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
   FILE *fp;

   fp = fopen("./test", "w+");

   fputs("1111111111111111", fp);
   fputs("P\336\377\377\377\177", fp);
   fputc(0, fp);
   fputc(0, fp);
   
   int Pass[6];
   Pass[0] = 153;
   Pass[1] = 71;
   Pass[2] = 85;
   Pass[3] = 85;
   Pass[4] = 85;
   Pass[5] = 85;
   
   for(int i=0; i<5; i++)
   {
      //printf("%s", &Pass[i]);
      fprintf(fp, "%s", &Pass[i]);
   }

   //fputc(0, fp);
   //fprintf(fp, "111");
   
   fclose(fp);

   return 0;
}
