#include<mlearning_matrix.h>
#include<mlearning_scale.h>
#include<mlearning_vector.h>
#include<stdlib.h>
#include<stdio.h>
#include<mlearning_utils.h>

mlearning_mat_double* mlearning_scale_double(char*dataset_file_name,mlearning_row_vec_string*columns_to_scale,char*parameters_file_name,char*algorithm,mlearning_mat_double*matrix)
{
mlearning_mat_double*scaled_column_matrix;
mlearning_mat_double*parameters_matrix;
mlearning_row_vec_string*m_header;
dimension_t columns_to_scale_size;
dimension_t m_header_size;
index_t i,j;
dimension_t matrix_rows,matrix_columns;
mlearning_mat_double*tmp_matrix;
char*column_name;
char*scale_column_name;
int algorithm_code;
int MIN_MAX_ALGORITHM=1;
int Z_SCORE_ALGORITHM=2;
if(dataset_file_name==NULL || columns_to_scale==NULL || parameters_file_name==NULL || algorithm==NULL) return NULL;

if(mlearning_string_equals_ignore_case(algorithm,"min-max")==0)
{
algorithm_code=MIN_MAX_ALGORITHM;
}
else if(mlearning_string_equals_ignore_case(algorithm,"z-score")==0)
{
algorithm_code=Z_SCORE_ALGORITHM;
}
else return NULL;

columns_to_scale_size=mlearning_row_vec_string_get_size(columns_to_scale);
if(columns_to_scale_size==0) 
{
return NULL;
}

if(algorithm_code==MIN_MAX_ALGORITHM)
{
parameters_matrix=mlearning_mat_double_create_new(2,columns_to_scale_size);
if(parameters_matrix==NULL)
{
return NULL;
}
}
else if(algorithm_code==Z_SCORE_ALGORITHM)
{
parameters_matrix=mlearning_mat_double_create_new(2,columns_to_scale_size);
if(parameters_matrix==NULL)
{
return NULL;
}
}

matrix=mlearning_mat_double_from_csv(dataset_file_name,matrix,&m_header);
if(matrix==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
return NULL;
}

mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);


m_header_size=mlearning_row_vec_string_get_size(m_header);
scaled_column_matrix=mlearning_mat_double_create_new(matrix_rows,1);
if(scaled_column_matrix==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
mlearning_mat_double_destroy(matrix);
mlearning_row_vec_string_destroy(m_header);
return NULL;
}

for(i=0;i<columns_to_scale_size;i++)
{
mlearning_row_vec_string_get(columns_to_scale,i,&scale_column_name);
if(scale_column_name==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_row_vec_string_destroy(m_header);
return NULL;
}

for(j=0;j<m_header_size;j++)
{
mlearning_row_vec_string_get(m_header,j,&column_name);
if(column_name==NULL)
{
free(scale_column_name);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_row_vec_string_destroy(m_header);
return NULL;
}

if(mlearning_string_equals_ignore_case(scale_column_name,column_name)==0)
{
//scale jth column
if(algorithm_code==MIN_MAX_ALGORITHM)
{ 
if(mlearning_scale_double_min_max(matrix,0,j,matrix_rows-1,j,&tmp_matrix,scaled_column_matrix)!=NULL)
{
mlearning_mat_double_copy(matrix,scaled_column_matrix,0,j,0,0,matrix_rows-1,0);
mlearning_mat_double_set(parameters_matrix,0,i,mlearning_mat_double_get(tmp_matrix,0,0));
mlearning_mat_double_set(parameters_matrix,1,i,mlearning_mat_double_get(tmp_matrix,1,0));
mlearning_mat_double_destroy(tmp_matrix);
}
else 
{
free(scale_column_name);
free(column_name);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_row_vec_string_destroy(m_header);
return NULL;
}
}
else if(algorithm_code==Z_SCORE_ALGORITHM)
{
if(mlearning_scale_double_z_score(matrix,0,j,matrix_rows-1,j,&tmp_matrix,scaled_column_matrix)!=NULL)
{
mlearning_mat_double_copy(matrix,scaled_column_matrix,0,j,0,0,matrix_rows-1,0);
mlearning_mat_double_set(parameters_matrix,0,i,mlearning_mat_double_get(tmp_matrix,0,0));
mlearning_mat_double_set(parameters_matrix,1,i,mlearning_mat_double_get(tmp_matrix,1,0));
mlearning_mat_double_destroy(tmp_matrix);
}
else 
{
free(scale_column_name);
free(column_name);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_row_vec_string_destroy(m_header);
return NULL;
}
}
free(column_name);
break;
}
free(column_name);
}  //inner loop end
free(scale_column_name);
if(j==m_header_size)
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
return NULL;
}
}  //outer loop end
mlearning_mat_double_to_csv(parameters_matrix,parameters_file_name,columns_to_scale);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(m_header);
mlearning_mat_double_destroy(scaled_column_matrix);
return matrix;
}

mlearning_mat_double* mlearning_scale_double_with_given_parameters(char*dataset_file_name,char*parameters_file_name,char*algorithm,mlearning_mat_double*matrix)
{
mlearning_mat_double*scaled_column_matrix;
mlearning_mat_double*tmp_matrix;
mlearning_row_vec_string*matrix_header;
mlearning_row_vec_string*columns_to_scale;
index_t i,j;
dimension_t matrix_rows,matrix_columns;
dimension_t columns_to_scale_size;
dimension_t matrix_header_size;
char*scale_column_name;
char*column_name;
int algorithm_code;
int MIN_MAX_ALGORITHM=1;
int Z_SCORE_ALGORITHM=2;
mlearning_mat_double*parameters_matrix;
if(dataset_file_name==NULL || parameters_file_name==NULL || algorithm==NULL) return NULL;

if(mlearning_string_equals_ignore_case(algorithm,"min-max")==0)
{
algorithm_code=MIN_MAX_ALGORITHM;
}else if(mlearning_string_equals_ignore_case(algorithm,"z-score")==0)
{
algorithm_code=Z_SCORE_ALGORITHM;
}
else return NULL;

parameters_matrix=mlearning_mat_double_from_csv(parameters_file_name,NULL,&columns_to_scale);
if(parameters_matrix==NULL) return NULL;
columns_to_scale_size=mlearning_row_vec_string_get_size(columns_to_scale);

matrix=mlearning_mat_double_from_csv(dataset_file_name,matrix,&matrix_header);
if(matrix==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
return NULL;
}
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
matrix_header_size=mlearning_row_vec_string_get_size(matrix_header);
scaled_column_matrix=mlearning_mat_double_create_new(matrix_rows,1);
if(scaled_column_matrix==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(matrix);
return NULL;
}
tmp_matrix=mlearning_mat_double_create_new(2,1);
if(tmp_matrix==NULL)
{
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(scaled_column_matrix);
return NULL;
}
for(i=0;i<columns_to_scale_size;i++)
{
mlearning_row_vec_string_get(columns_to_scale,i,&scale_column_name);
if(scale_column_name==NULL)
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);
return NULL;
}
for(j=0;j<matrix_header_size;j++)
{
mlearning_row_vec_string_get(matrix_header,j,&column_name);
if(column_name==NULL)
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);
free(scale_column_name);
return NULL;
}
if(mlearning_string_equals_ignore_case(scale_column_name,column_name)==0)
{
if(algorithm_code==MIN_MAX_ALGORITHM)
{
mlearning_mat_double_set(tmp_matrix,0,0,mlearning_mat_double_get(parameters_matrix,0,i));
mlearning_mat_double_set(tmp_matrix,1,0,mlearning_mat_double_get(parameters_matrix,1,i));
if(mlearning_scale_double_with_given_min_max(matrix,0,j,matrix_rows-1,j,tmp_matrix,scaled_column_matrix)!=NULL)
{
mlearning_mat_double_copy(matrix,scaled_column_matrix,0,j,0,0,matrix_rows-1,0);
}
else 
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);
free(scale_column_name);
free(column_name);
return NULL;
}

}else if(algorithm_code==Z_SCORE_ALGORITHM)
{
mlearning_mat_double_set(tmp_matrix,0,0,mlearning_mat_double_get(parameters_matrix,0,i));
mlearning_mat_double_set(tmp_matrix,1,0,mlearning_mat_double_get(parameters_matrix,1,i));
if(mlearning_scale_double_z_score_with_given_mean_standard_deviation(matrix,0,j,matrix_rows-1,j,tmp_matrix,scaled_column_matrix)!=NULL)
{
mlearning_mat_double_copy(matrix,scaled_column_matrix,0,j,0,0,matrix_rows-1,0);
}
else 
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);
free(scale_column_name);
free(column_name);
return NULL;
}
}
free(column_name);
break;
}
free(column_name);
}
free(scale_column_name);
if(j==matrix_header_size)  //not found the column to scale in matrix_header
{
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);

return NULL;
}
}


mlearning_mat_double_destroy(parameters_matrix);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_row_vec_string_destroy(matrix_header);
mlearning_mat_double_destroy(scaled_column_matrix);
mlearning_mat_double_destroy(tmp_matrix);


return matrix;
}


mlearning_mat_double* mlearning_scale_double_min_max(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlearning_mat_double** min_max_matrix,mlearning_mat_double*scaled_matrix)
{
index_t r,c,i;
dimension_t matrix_rows,matrix_columns;
dimension_t scaled_matrix_rows,scaled_matrix_columns;
dimension_t scaled_matrix_r,scaled_matrix_c;
dimension_t s_rows,s_columns;
double*min;
double*max;
double value;
double scaled_value;
if(matrix==NULL || min_max_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index) return NULL;
if(start_column_index>end_column_index) return NULL;
scaled_matrix_rows=end_row_index-start_row_index+1;
scaled_matrix_columns=end_column_index-start_column_index+1;

if(scaled_matrix==NULL)
{
scaled_matrix=mlearning_mat_double_create_new(scaled_matrix_rows,scaled_matrix_columns);
if(scaled_matrix==NULL) return NULL;
}
else 
{
mlearning_mat_double_get_dimensions(scaled_matrix,&s_rows,&s_columns);
if(s_rows!=scaled_matrix_rows || s_columns!=scaled_matrix_columns) return NULL;
}
*min_max_matrix=mlearning_mat_double_create_new(2,scaled_matrix_columns);
if(*min_max_matrix==NULL)
{
return NULL;
}

max=(double*)malloc(sizeof(double)*scaled_matrix_columns);
if(max==NULL) 
{
mlearning_mat_double_destroy(*min_max_matrix);
*min_max_matrix=NULL;
return NULL;
}
min=(double*)malloc(sizeof(double)*scaled_matrix_columns);
if(min==NULL)
{
free(max);
mlearning_mat_double_destroy(*min_max_matrix);
*min_max_matrix=NULL;
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
for(scaled_matrix_r=0;scaled_matrix_r<scaled_matrix_rows;scaled_matrix_r++)
{
c=start_column_index;
for(scaled_matrix_c=0;scaled_matrix_c<scaled_matrix_columns;scaled_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
scaled_value=(value-min[scaled_matrix_c])/(max[scaled_matrix_c]-min[scaled_matrix_c]);
mlearning_mat_double_set(scaled_matrix,scaled_matrix_r,scaled_matrix_c,scaled_value);
c++;
}
r++;    
}

for(i=0;i<scaled_matrix_columns;i++)
{
mlearning_mat_double_set(*min_max_matrix,0,i,min[i]); //0 row contains min values
mlearning_mat_double_set(*min_max_matrix,1,i,max[i]);  //1 row contains max values
}
free(min);
free(max);
return scaled_matrix;
}


mlearning_mat_double * mlearning_scale_double_with_given_min_max(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlearning_mat_double*min_max_matrix,mlearning_mat_double*scaled_matrix)
{
index_t r,c;
dimension_t matrix_rows,matrix_columns;
dimension_t scaled_matrix_rows,scaled_matrix_columns;
dimension_t scaled_matrix_r,scaled_matrix_c;
dimension_t min_max_rows,min_max_columns;
dimension_t s_rows,s_columns;
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
scaled_matrix_rows=end_row_index-start_row_index+1;
scaled_matrix_columns=end_column_index-start_column_index+1;
if(min_max_rows!=2) return NULL;  //0th row for min value and 1st row for max value
if(min_max_columns!=scaled_matrix_columns) return NULL;

if(scaled_matrix==NULL)
{
scaled_matrix=mlearning_mat_double_create_new(scaled_matrix_rows,scaled_matrix_columns);
if(scaled_matrix==NULL) return NULL;
}
else 
{
mlearning_mat_double_get_dimensions(scaled_matrix,&s_rows,&s_columns);
if(s_rows!=scaled_matrix_rows || s_columns!=scaled_matrix_columns) return NULL;
}


r=start_row_index;
for(scaled_matrix_r=0;scaled_matrix_r<scaled_matrix_rows;scaled_matrix_r++)
{
c=start_column_index;
for(scaled_matrix_c=0;scaled_matrix_c<scaled_matrix_columns;scaled_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
min=mlearning_mat_double_get(min_max_matrix,0,scaled_matrix_c);  //0th row min values
max=mlearning_mat_double_get(min_max_matrix,1,scaled_matrix_c);  //1st row max values
scaled_value=((value-min)/(max-min));
mlearning_mat_double_set(scaled_matrix,scaled_matrix_r,scaled_matrix_c,scaled_value);
c++;
}
r++;
}
return scaled_matrix;
}
mlearning_column_vec_double*mlearning_scale_column_vec_double_with_given_min_max(mlearning_column_vec_double*vector,index_t from_index,index_t to_index,mlearning_mat_double*min_max_matrix,mlearning_column_vec_double*scaled_column_vec)
{
index_t i;
dimension_t min_max_rows,min_max_columns;
double value,scaled_value;
dimension_t scaled_column_vec_size;
dimension_t size;
double min,max;
dimension_t vector_size;
if(vector==NULL) return NULL;
if(min_max_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(min_max_matrix,&min_max_rows,&min_max_columns);
vector_size=mlearning_column_vec_double_get_size(vector);
if(from_index>to_index) return NULL;
scaled_column_vec_size=to_index-from_index+1;
if(min_max_rows!=2) return NULL;  //0th row for min value and 1st row for max value
if(min_max_columns!=vector_size) return NULL;

if(scaled_column_vec==NULL)
{
scaled_column_vec=mlearning_column_vec_double_create_new(scaled_column_vec_size);
if(scaled_column_vec==NULL) return NULL;
}
else 
{
size=mlearning_column_vec_double_get_size(scaled_column_vec);
if(size!=scaled_column_vec_size) return NULL;
}


for(i=from_index;i<=to_index;i++)
{
value=mlearning_column_vec_double_get(vector,i);
min=mlearning_mat_double_get(min_max_matrix,0,i);
max=mlearning_mat_double_get(min_max_matrix,1,i);
scaled_value=((value-min)/(max-min));
mlearning_column_vec_double_set(scaled_column_vec,i,scaled_value);
}
return scaled_column_vec;
}

mlearning_row_vec_double*mlearning_scale_row_vec_double_with_given_min_max(mlearning_row_vec_double*vector,index_t from_index,index_t to_index,mlearning_mat_double*min_max_matrix,mlearning_row_vec_double*scaled_row_vec)
{
index_t i;
dimension_t min_max_rows,min_max_columns;
double value,scaled_value;
dimension_t scaled_row_vec_size;
double min,max;
dimension_t size;
dimension_t vector_size;
if(vector==NULL) return NULL;
if(min_max_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(min_max_matrix,&min_max_rows,&min_max_columns);
vector_size=mlearning_row_vec_double_get_size(vector);
if(from_index>to_index) return NULL;
scaled_row_vec_size=to_index-from_index+1;
if(min_max_rows!=2) return NULL;  //0th row for min value and 1st row for max value
if(min_max_columns!=vector_size) return NULL;

if(scaled_row_vec==NULL)
{
scaled_row_vec=mlearning_row_vec_double_create_new(scaled_row_vec_size);
if(scaled_row_vec==NULL) return NULL;
}
else 
{
size=mlearning_row_vec_double_get_size(scaled_row_vec);
if(size!=scaled_row_vec_size) return NULL;
}


for(i=from_index;i<=to_index;i++)
{
value=mlearning_row_vec_double_get(vector,i);
min=mlearning_mat_double_get(min_max_matrix,0,i);
max=mlearning_mat_double_get(min_max_matrix,1,i);
scaled_value=((value-min)/(max-min));
mlearning_row_vec_double_set(scaled_row_vec,i,scaled_value);
}
return scaled_row_vec;
}

mlearning_mat_double* mlearning_scale_double_z_score(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlearning_mat_double** mean_standard_deviation_matrix,mlearning_mat_double*scaled_matrix)
{
double value,scaled_value;
double *mean,*standard_deviation;
dimension_t scaled_matrix_rows;
dimension_t scaled_matrix_columns;
index_t scaled_matrix_r,scaled_matrix_c;
index_t r,c,i;
dimension_t s_rows,s_columns;
dimension_t matrix_rows;
dimension_t matrix_columns;
if(matrix==NULL || mean_standard_deviation_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
if(start_row_index<0 || start_column_index<0) return NULL;
if(end_row_index>=matrix_rows || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
scaled_matrix_rows=end_row_index-start_row_index+1;
scaled_matrix_columns=end_column_index-start_column_index+1;
if(scaled_matrix==NULL)
{
scaled_matrix=mlearning_mat_double_create_new(scaled_matrix_rows,scaled_matrix_columns);
if(scaled_matrix==NULL) return NULL;
}
else 
{
mlearning_mat_double_get_dimensions(scaled_matrix,&s_rows,&s_columns);
if(s_rows!=scaled_matrix_rows || s_columns!=scaled_matrix_columns) return NULL;
}
*mean_standard_deviation_matrix=mlearning_mat_double_create_new(2,scaled_matrix_columns);
if(*mean_standard_deviation_matrix==NULL) return NULL;
mean=(double*)malloc(sizeof(double)*scaled_matrix_columns);
if(mean==NULL)
{
mlearning_mat_double_destroy(*mean_standard_deviation_matrix);
*mean_standard_deviation_matrix=NULL;
 return NULL;
}
standard_deviation=(double*)malloc(sizeof(double)*scaled_matrix_columns);
if(standard_deviation==NULL)
{
free(mean);
mlearning_mat_double_destroy(*mean_standard_deviation_matrix);
*mean_standard_deviation_matrix=NULL;
return NULL;
}
i=0;
for(c=start_column_index;c<=end_column_index;c++)
{
mean[i]=mlearning_mat_double_get_mean(matrix,start_row_index,c,end_row_index,c);
standard_deviation[i]=mlearning_mat_double_get_standard_deviation(matrix,start_row_index,c,end_row_index,c);
i++;
}
r=start_row_index;
for(scaled_matrix_r=0;scaled_matrix_r<scaled_matrix_rows;scaled_matrix_r++)
{
c=start_column_index;
for(scaled_matrix_c=0;scaled_matrix_c<scaled_matrix_columns;scaled_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
scaled_value=(value-mean[scaled_matrix_c])/(standard_deviation[scaled_matrix_c]);
mlearning_mat_double_set(scaled_matrix,scaled_matrix_r,scaled_matrix_c,scaled_value);
c++;
}
r++;
}


for(i=0;i<scaled_matrix_columns;i++)
{
mlearning_mat_double_set(*mean_standard_deviation_matrix,0,i,mean[i]);
mlearning_mat_double_set(*mean_standard_deviation_matrix,1,i,standard_deviation[i]);
}

free(mean);
free(standard_deviation);
return scaled_matrix;
}

mlearning_mat_double* mlearning_scale_double_z_score_with_given_mean_standard_deviation(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,mlearning_mat_double*mean_standard_deviation_matrix,mlearning_mat_double*scaled_matrix)
{
index_t r,c;
dimension_t matrix_rows,matrix_columns;
dimension_t scaled_matrix_rows,scaled_matrix_columns;
dimension_t scaled_matrix_r,scaled_matrix_c;
dimension_t mean_sd_rows,mean_sd_columns;
dimension_t s_rows,s_columns;
double mean;
double standard_deviation;
double value;
double scaled_value; 
if(matrix==NULL || mean_standard_deviation_matrix==NULL) return NULL;
mlearning_mat_double_get_dimensions(mean_standard_deviation_matrix,&mean_sd_rows,&mean_sd_columns);
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
if(start_row_index>end_row_index) return NULL;
if(start_column_index>end_column_index) return NULL;
scaled_matrix_rows=end_row_index-start_row_index+1;
scaled_matrix_columns=end_column_index-start_column_index+1;
if(mean_sd_rows!=2) return NULL;  //0th row for min value and 1st row for max value
if(mean_sd_columns!=scaled_matrix_columns) return NULL;

if(scaled_matrix==NULL)
{
scaled_matrix=mlearning_mat_double_create_new(scaled_matrix_rows,scaled_matrix_columns);
if(scaled_matrix==NULL) return NULL;
}
else 
{
mlearning_mat_double_get_dimensions(scaled_matrix,&s_rows,&s_columns);
if(s_rows!=scaled_matrix_rows || s_columns!=scaled_matrix_columns) return NULL;
}  


r=start_row_index;
for(scaled_matrix_r=0;scaled_matrix_r<scaled_matrix_rows;scaled_matrix_r++)
{
c=start_column_index;
for(scaled_matrix_c=0;scaled_matrix_c<scaled_matrix_columns;scaled_matrix_c++)
{
value=mlearning_mat_double_get(matrix,r,c);
mean=mlearning_mat_double_get(mean_standard_deviation_matrix,0,scaled_matrix_c);  //0th row min values
standard_deviation=mlearning_mat_double_get(mean_standard_deviation_matrix,1,scaled_matrix_c);  //1st row max values
scaled_value=((value-mean)/standard_deviation);
mlearning_mat_double_set(scaled_matrix,scaled_matrix_r,scaled_matrix_c,scaled_value);
c++;
}
r++;
}
return scaled_matrix;

}
