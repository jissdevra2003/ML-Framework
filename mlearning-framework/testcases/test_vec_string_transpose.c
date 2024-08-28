#include<stdio.h>
#include<stdlib.h>
#include<mlearning_vector.h>
int main()
{
mlearning_row_vec_string*R_vector;
dimension_t vec_size;
index_t i;
char*str;
R_vector=mlearning_row_vec_string_create_new(3);
mlearning_row_vec_string_set(R_vector,0,"Jiss");
mlearning_row_vec_string_set(R_vector,1,"Thomas");
mlearning_row_vec_string_set(R_vector,2,"Walter");
mlearning_column_vec_string*C_vector;
C_vector=mlearning_row_vec_string_transpose(R_vector);
vec_size=mlearning_column_vec_string_get_size(C_vector);
printf("Size of transposed column vector is %d\n",vec_size);
for(i=0;i<vec_size;i++)
{
mlearning_column_vec_string_get(C_vector,i,&str);
if(str!=NULL) printf("%s\n",str);
free(str);
}
return 0;
}