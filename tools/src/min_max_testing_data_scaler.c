#include<stdio.h>
#include<mlearning_scale.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
char*input_file;
char*output_file;
char*min_max_file;
dimension_t matrix_rows,matrix_columns;
index_t from_column_index;
index_t to_column_index;
mlearning_row_vec_string*header;
mlearning_row_vec_string*min_max_header;
mlearning_mat_double*matrix;
mlearning_mat_double*scaled_matrix;
mlearning_mat_double*min_max_matrix;

if(argc!=6)
{
printf("Usage : min_max_scaler _ input_file _ output_file _ from_column_index _ to_column_index _ min_max_file\n");
return 0;
}
input_file=argv[1];
output_file=argv[2];
from_column_index=atoi(argv[3]);
to_column_index=atoi(argv[4]);
min_max_file=argv[5];

matrix=mlearning_mat_double_from_csv(input_file,NULL,&header);
if(matrix==NULL)
{
printf("Low memory\n");
return 0;
}
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
min_max_matrix=mlearning_mat_double_from_csv(min_max_file,NULL,&min_max_header);
if(min_max_matrix==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(matrix);
mlearning_row_vec_string_destroy(header);
return 0;
}
              
scaled_matrix=mlearning_scale_double_with_given_min_max(matrix,0,from_column_index,matrix_rows-1,to_column_index,min_max_matrix,NULL);
if(scaled_matrix==NULL)
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(min_max_matrix);
mlearning_row_vec_string_destroy(header);
mlearning_row_vec_string_destroy(min_max_header);
return 0;
}
mlearning_mat_double_to_csv(scaled_matrix,output_file,header);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(scaled_matrix);
mlearning_mat_double_destroy(min_max_matrix);
mlearning_row_vec_string_destroy(header);
mlearning_row_vec_string_destroy(min_max_header);

return 0;

}