#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<stdlib.h>
#include<stdio.h>


void test_mean()
{
mlearning_column_vec_double*vector;
double x,mean;
dimension_t vector_size;
index_t i;
vector=mlearning_column_vec_double_create_new(5);
if(vector==NULL)
{
printf("Low memory\n");
return;
}
vector_size=mlearning_column_vec_double_get_size(vector);
x=1001.00;
for(i=0;i<vector_size;i++)
{
mlearning_column_vec_double_set(vector,i,x);
x+=20.00;
}
printf("Contents of vector are :");
for(i=0;i<vector_size;i++)
{
x=mlearning_column_vec_double_get(vector,i);
printf("%lf\n",x);
}
mean=mlearning_column_vec_double_get_mean(vector);
printf("Mean is %lf\n",mean);

}
void train_it()
{
mlearning_mat_double*dataset;
dimension_t dataset_rows;
dimension_t dataset_columns;

mlearning_mat_double*I;
dimension_t I_rows;
dimension_t I_columns;

mlearning_column_vec_double*A;
mlearning_column_vec_double*m;
mlearning_column_vec_double*P;
mlearning_column_vec_double*E;
mlearning_row_vec_double*ET;
mlearning_column_vec_double*ETE;
double sum_of_squared_error_values;
double final_error_value;

dataset=mlearning_mat_double_from_csv("IceCreamSales.csv");
if(dataset==NULL)
{
printf("Unable to load the csv file IceCreamSales.csv");
return;
}
mlearning_mat_double_get_dimensions(dataset,&dataset_rows,&dataset_columns);


I_rows=dataset_rows;
I_columns=dataset_columns-1+1;


I=mlearning_mat_double_create_new(I_rows,I_columns);
if(I==NULL)
{
printf("Unable to create matrix I\n");
mlearning_mat_double_destroy(dataset);
return;
}

mlearning_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,0);

mlearning_mat_double_fill(I,0,0,I_rows-1,0,1.0);  //input matrix m 1 fill krna hh

A=mlearning_mat_double_create_column_vec(dataset,1);
if(A==NULL)
{
printf("Unable to create column vector A\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
return;
}

m=mlearning_column_vec_double_create_new_filled(I_columns,0.0);  // 'm' column vector
if(m==NULL)
{
printf("Unable to create column vector m\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
return;
}
P=mlearning_multiply_double_matrix_with_column_vector(I,m);
if(P==NULL)
{
printf("Unable to create column vector P\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
return;
}

E=mlearning_subtract_double_column_vector(P,A);
if(E==NULL)
{
printf("Unable to create column vector E\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(m);
return;
}

ET=mlearning_column_vec_double_transpose(E);
if(ET==NULL)
{
printf("Unable to create row vector ET\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(E);
return;
}

ETE=mlearning_multiply_double_row_vector_with_column_vector(ET,E);
if(ETE==NULL)
{
printf("Unable to create column vector ETE\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
return;
}

sum_of_squared_error_values=mlearning_column_vec_double_get(ETE,0);
final_error_value=(sum_of_squared_error_values/I_rows);

printf("Sum of squared error values :%-41.15lf\n",sum_of_squared_error_values);
printf("Final error value :%-41.15lf\n",final_error_value);

//logic to update m & c values technically our m column vector.

//release resources
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);

}

int main()
{
//train_it();
test_mean();
return 0;
}