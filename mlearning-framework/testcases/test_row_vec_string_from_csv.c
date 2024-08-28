#include<mlearning_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlearning_row_vec_string*vector;
index_t i;
dimension_t vec_size;
char*string;
vector=mlearning_row_vec_string_from_csv("vecFile.csv");
vec_size=mlearning_row_vec_string_get_size(vector);
for(i=0;i<vec_size;i++)
{
mlearning_row_vec_string_get(vector,i,&string);
printf("%s\n",string);
free(string);
}
mlearning_row_vec_string_get(vector,2,&string);
printf("%s\n",string);
free(string);
mlearning_row_vec_string_destroy(vector);
return 0;
}