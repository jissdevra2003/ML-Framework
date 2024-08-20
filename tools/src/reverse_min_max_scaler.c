#include<stdio.h>
#include<stdlib.h>
#include<mlearning_scale.h>
int main(int argc,char*argv[])
{
char*input_file;
char*output_file;
char*min_max_file;
index_t r,c;
mlearning_mat_double*matrix;
mlearning_mat_double*min_max_matrix;
dimension_t matrix_rows,matrix_columns;
dimension_t min_max_rows,min_max_columns;
double value;
double min;
double max;
double s_value;
if(argc!=4)
{
printf("Usage : reverse_scale_output.exe _ input_file _ output_file _ min_max_file\n");
return 0;
}
input_file=argv[1];
output_file=argv[2];
min_max_file=argv[3];
matrix=mlearning_mat_double_from_csv(input_file);
if(matrix==NULL)
{
printf("Low memory\n");
return 0;
}
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
min_max_matrix=mlearning_mat_double_from_csv(min_max_file);
if(min_max_matrix==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(matrix);
return 0;
}
mlearning_mat_double_get_dimensions(min_max_matrix,&min_max_rows,&min_max_columns);

min=mlearning_mat_double_get(min_max_matrix,0,min_max_columns-1);
max=mlearning_mat_double_get(min_max_matrix,1,min_max_columns-1);
for(r=0;r<matrix_rows;r++)
{
for(c=matrix_columns-2;c<matrix_columns;c++)
{
s_value=mlearning_mat_double_get(matrix,r,c);
value=(s_value*(max-min))+min;
mlearning_mat_double_set(matrix,r,c,value);
}
}
mlearning_mat_double_to_csv(matrix,output_file);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(min_max_matrix);


return 0;
}