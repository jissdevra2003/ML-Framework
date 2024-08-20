//program to generate different random numbers
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
int x,k;
srand(time(NULL));
for(x=1;x<=5;x++)
{
k=rand();
printf("%d\n",k);
}
return 0;
}