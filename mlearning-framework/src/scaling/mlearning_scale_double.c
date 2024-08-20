#include<mlearning_matrix.h>
#include<mlearning_scale.h>
#include<stdlib.h>
#include<stdio.h>
mlearning_mat_double* mlearning_scale_double_min_max(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,char*min_max_file)
{
index_t r,c,i;
FILE*file; 
dimension_t matrix_rows,matrix_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_r,new_matrix_c;
mlearning_mat_double*new_matrix;
double*min;
double*max;
double value;
double scaled_value;
if(matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index) return NULL;
if(start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
new_matrix=mlearning_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
max=(double*)malloc(sizeof(double)*new_matrix_columns);
if(max==NULL) return NULL;
min=(double*)malloc(sizeof(double)*new_matrix_columns);
if(min==NULL)
{
free(max);
return NULL;
}

i=0;
for(c=start_column_index;c<=end_column_index;c++)
{
min[i]=mlearning_mat_double_get_minimum(matrix,start_row_index,c,end_row_index,c);
max[i]=mlearning_mat_double_get_maximum(matrix,start_row_index,c,end_row_index,c);
i++;
}
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
scaled_value=(value-min[new_matrix_c])/(max[new_matrix_c]-min[new_matrix_c]);
mlearning_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
c++;
}
r++;    
}
file=fopen(min_max_file,"w");
if(file==NULL)
{
free(min);
free(max);
mlearning_mat_double_destroy(new_matrix);
return NULL;
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",min[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<new_matrix_columns;i++)
{
fprintf(file,"%lf",max[i]);
if(i==new_matrix_columns-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
free(min);
free(max);
return new_matrix;
}


mlearning_mat_double * mlearning_scale_double_with_given_min_max(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlearning_mat_double*min_max_matrix)
{
index_t r,c;
dimension_t matrix_rows,matrix_columns;
dimension_t new_matrix_rows,new_matrix_columns;
dimension_t new_matrix_r,new_matrix_c;
dimension_t min_max_rows,min_max_columns;
mlearning_mat_double*new_matrix;
double min;
double max;
double value;
double scaled_value;
if(matrix==NULL || min_max_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(min_max_matrix,&min_max_rows,&min_max_columns);
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index) return NULL;
if(start_column_index>end_column_index) return NULL;
new_matrix_rows=end_row_index-start_row_index+1;
new_matrix_columns=end_column_index-start_column_index+1;
if(min_max_rows!=2) return NULL;  //0th row for min value and 1st row for max value
if(min_max_columns!=new_matrix_columns) return NULL;
new_matrix=mlearning_mat_double_create_new(new_matrix_rows,new_matrix_columns);
if(new_matrix==NULL) return NULL;
r=start_row_index;
for(new_matrix_r=0;new_matrix_r<new_matrix_rows;new_matrix_r++)
{
c=start_column_index;
for(new_matrix_c=0;new_matrix_c<new_matrix_columns;new_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
min=mlearning_mat_double_get(min_max_matrix,0,new_matrix_c);  //0th row min values
max=mlearning_mat_double_get(min_max_matrix,1,new_matrix_c);  //1st row max values
scaled_value=((value-min)/(max-min));
mlearning_mat_double_set(new_matrix,new_matrix_r,new_matrix_c,scaled_value);
c++;
}
r++;
}
return new_matrix;
}