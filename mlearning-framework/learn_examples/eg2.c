//program to generate random numbers between two given number , including the given two numbers
#include<stdio.h>

#include<stdlib.h>
#include<time.h>
int main()
{
int a,b;
int x,k,r;
a=10;
b=56;
srand(time(NULL));
for(x=1;x<=10;x++)
{
r=rand();
k=(r%(b-a+1))+a;
printf("%d\n",k);
}
return 0;

}