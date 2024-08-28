#include<stdio.h>
#include<mlearning_vector.h>
#include<mlearning_matrix.h>
#include<mlearning_operations.h>
mlearning_column_vec_double*mlearning_multiply_double_row_vector_with_column_vector(mlearning_row_vec_double*left_vector,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*product_vector)
{
if(left_vector==NULL || right_vector==NULL) return NULL;
dimension_t left_vector_size;
dimension_t right_vector_size;
double product;
double left_vector_value;
double right_vector_value;
index_t i;
left_vector_size=mlearning_row_vec_double_get_size(left_vector);
right_vector_size=mlearning_column_vec_double_get_size(right_vector);
if(left_vector_size!=right_vector_size) return NULL;
product=0.0;

if(product_vector==NULL)
{
product_vector=mlearning_column_vec_double_create_new(1);
if(product_vector==NULL) return NULL;
}
else 
{
if(mlearning_column_vec_double_get_size(product_vector)!=1) return NULL;
}

for(i=0;i<left_vector_size;i++)
{
left_vector_value=mlearning_row_vec_double_get(left_vector,i);
right_vector_value=mlearning_column_vec_double_get(right_vector,i);
product=product+(left_vector_value*right_vector_value);
}
mlearning_column_vec_double_set(product_vector,0,product);
return product_vector;
}
mlearning_column_vec_double*mlearning_multiply_double_matrix_with_column_vector(mlearning_mat_double*left_matrix,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*product_vector)
{
if(left_matrix==NULL || right_vector==NULL) return NULL;
dimension_t left_matrix_rows;
dimension_t left_matrix_columns;
dimension_t right_vector_size;

double product;
index_t r,c;
double left_matrix_value;
double right_vector_value;

mlearning_mat_double_get_dimensions(left_matrix,&left_matrix_rows,&left_matrix_columns);
right_vector_size=mlearning_column_vec_double_get_size(right_vector);

if(left_matrix_columns!=right_vector_size) return NULL;


if(product_vector==NULL)
{
product_vector=mlearning_column_vec_double_create_new(left_matrix_rows);
if(product_vector==NULL) return NULL;
}
else 
{
if(mlearning_column_vec_double_get_size(product_vector)!=left_matrix_rows) return NULL;
}

for(r=0;r<left_matrix_rows;r++)
{
product=0.0;
for(c=0;c<left_matrix_columns;c++)
{
left_matrix_value=mlearning_mat_double_get(left_matrix,r,c);
right_vector_value=mlearning_column_vec_double_get(right_vector,c);
product=product+(left_matrix_value*right_vector_value);
}
mlearning_column_vec_double_set(product_vector,r,product);
}
return product_vector;
}
mlearning_column_vec_double*mlearning_subtract_double_column_vector(mlearning_column_vec_double*left_vector,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*difference_vector)
{
if(left_vector==NULL || right_vector==NULL) return NULL;
double left_vector_value;
double right_vector_value;
dimension_t left_vector_size;
dimension_t right_vector_size;
double difference;
index_t i;
left_vector_size=mlearning_column_vec_double_get_size(left_vector);
right_vector_size=mlearning_column_vec_double_get_size(right_vector);
if(left_vector_size!=right_vector_size) return NULL;
difference=0.0;

if(difference_vector==NULL)
{
difference_vector=mlearning_column_vec_double_create_new(left_vector_size);
if(difference_vector==NULL) return NULL;
}
else 
{
if(mlearning_column_vec_double_get_size(difference_vector)!=left_vector_size) return NULL;
}

for(i=0;i<left_vector_size;i++)
{
left_vector_value=mlearning_column_vec_double_get(left_vector,i);
right_vector_value=mlearning_column_vec_double_get(right_vector,i);
difference=(left_vector_value-right_vector_value);
mlearning_column_vec_double_set(difference_vector,i,difference);
}
return difference_vector;
}

mlearning_column_vec_double*mlearning_multiply_double_scalar_with_column_vector(double scalar_value,mlearning_column_vec_double*vector,mlearning_column_vec_double*product_vector)
{
index_t i;
double value;
double product;
dimension_t vector_size;
if(vector==NULL) return NULL;
vector_size=mlearning_column_vec_double_get_size(vector);

if(product_vector==NULL) 
{
product_vector=mlearning_column_vec_double_create_new(vector_size);
if(product_vector==NULL) return NULL;
}
else 
{
if(mlearning_column_vec_double_get_size(product_vector)!=vector_size) return NULL;
}

for(i=0;i<vector_size;i++)
{
value=mlearning_column_vec_double_get(vector,i);
product=scalar_value*value;
mlearning_column_vec_double_set(product_vector,i,product);
}
return product_vector;
}

