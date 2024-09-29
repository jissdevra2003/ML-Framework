#include<mlearning_encoder.h>
#include<mlearning_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{

index_t i;
char*input_file;
char*ptr;
char*output_file;
mlearning_row_vec_string*encode_columns_vector;
if(argc<4)
{
printf("Usage : one_hot_encoding _ input_file _ output_file _ column_name1 column_name2 and more..\n");
return 0;
}
//1st arg:source file name
//2ns arg:target file name
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



//for testing encode_columns array
// printf("size is %u\n",size);
// for(i=0;i<size;i++)
// {
// printf("%u\n",encode_columns[i]);
// }

return 0;
}