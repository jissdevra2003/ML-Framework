#include<mlearning_encoder.h>
<<<<<<< HEAD
#include<mlearning_vector.h>
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
<<<<<<< HEAD

index_t i;
char*input_file;
char*ptr;
char*output_file;
mlearning_row_vec_string*encode_columns_vector;
if(argc<4)
{
printf("Usage : one_hot_encoding _ input_file _ output_file _ column_name1 column_name2 and more..\n");
=======
int* encode_columns;
dimension_t size;
char*s,*e;
index_t i;
char*input_file;
char*output_file;
char*columns_string;
char has_header;
int header_exists;
if(argc!=5)
{
printf("Usage : one_hot_encoding.exe _ input_file _ output_file _ columns_string _ has_header\n");
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
return 0;
}
//1st arg:source file name
//2ns arg:target file name
<<<<<<< HEAD
//3rd arg:encode columns names 


input_file=argv[1];
output_file=argv[2];
encode_columns_vector=mlearning_row_vec_string_create_new(argc-3);
for(i=3;i<argc;++i)
{
mlearning_row_vec_string_set(encode_columns_vector,i-3,argv[i]);
}
//for testing
for(i=3;i<argc;i++)
{
mlearning_row_vec_string_get(encode_columns_vector,i-3,&ptr);
printf("%s ",ptr);
}
mlearning_encoder_encode_one_hot(input_file,output_file,encode_columns_vector);
mlearning_row_vec_string_destroy(encode_columns_vector);
return 0;



=======
//3rd arg:encode columns array base address
//4th arg:header exists or not 0(false) 1 or non zero(true)

input_file=argv[1];
output_file=argv[2];
columns_string=argv[3];
has_header=argv[4][0];
if(has_header=='y' || has_header=='Y') header_exists=1;
else header_exists=0;

i=0;
size=0;
for(i=0;columns_string[i]!='\0';i++)
{
if(columns_string[i]==',') size++;
}
size++;

encode_columns=(int*)malloc(sizeof(int)*size);
if(encode_columns==NULL)
{
printf("Low memory\n");
return 0;
}
i=0;
s=columns_string;
while(1)
{
e=s+1;
while(*e!='\0' && *e!=',') e++;
if(*e=='\0')
{
encode_columns[i]=atoi(s);
break;
}
else
{
*e='\0';
encode_columns[i]=atoi(s);
i++;
s=e+1;
}
}
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
//for testing encode_columns array
// printf("size is %u\n",size);
// for(i=0;i<size;i++)
// {
// printf("%u\n",encode_columns[i]);
// }
<<<<<<< HEAD

=======
mlearning_encoder_encode_one_hot(input_file,output_file,encode_columns,size,header_exists);
free(encode_columns);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
return 0;
}