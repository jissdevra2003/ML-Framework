#include<mlearning_encoder.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
int encode_columns[3]={1,4,5};
//1st arg:source file name
//2ns arg:target file name
//3rd arg:encode columns array base address
//4th arg:size of encode_column array
//5th arg:header exists or not 0(false) 1 or non zero(true)
mlearning_encoder_encode_one_hot("insurance.csv","one_hot_encoded_insurance.csv",encode_columns,3,1);
printf("Hot encoded file generated in (one_hot_encoded_insurance.csv)\n");
return 0;
}