#include<mlearning_vector.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
mlearning_row_vec_string*vector;
index_t i;
char*str;
dimension_t vec_size;
vector=mlearning_row_vec_string_create_new(4);
mlearning_row_vec_string_set(vector,0,"Jiss");
mlearning_row_vec_string_set(vector,1,"Thomas");
mlearning_row_vec_string_set(vector,2,"Walter");
mlearning_row_vec_string_set(vector,3,"Jesse");

vec_size=mlearning_row_vec_string_get_size(vector);
for(i=0;i<vec_size;i++)
{
mlearning_row_vec_string_get(vector,i,&str);
printf("%s\n",str);
free(str);
}
printf("Vector size : %d",vec_size);
mlearning_row_vec_string_to_csv(vector,"vecFile.csv");
mlearning_row_vec_string_destroy(vector);

return 0;
}