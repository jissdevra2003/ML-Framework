#include<mlearning_utils.h>
#include<stdio.h>
#include<inttypes.h>

int mlearning_string_equals_ignore_case(const char*left,const char*right)
{
char c1,c2;
if(left==NULL && right==NULL) return 0;
if(left==NULL) return -1;
if(right==NULL) return 1;
while(*left!='\0' && *right!='\0')
{
c1=*left;
c2=*right;
if(c1>=97 && c1<=122) c1-=32;
if(c2>=97 && c2<=122) c2-=32;
if(c1!=c2) return c1-c2;
left++;
right++;
}
return (*left)-(*right);
}

void mlearning_number_to_binary_string(uint32_t num,char*b_string)
{

int i,j;
int bit;
for(j=0,i=31;i>=0;i--,j++)
{
//right shift by i and then and(&) opeartion with 1
bit=(num>>i) & 1;
if(bit==0) b_string[j]='0';
else b_string[j]='1';
}
b_string[j]='\0';
 

}