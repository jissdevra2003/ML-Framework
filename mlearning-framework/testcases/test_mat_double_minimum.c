#include<mlearning_matrix.h>
#include<stdio.h>
int main()
{
index_t r,c;
index_t matrix_rows,matrix_columns;
double x=7.96;
double min,value;
mlearning_mat_double*matrix;
matrix=mlearning_mat_double_create_new(3,4);
mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
for(r=0;r<matrix_rows;r++)
{
for(c=0;c<matrix_columns;c++)
{
mlearning_mat_double_set(matrix,r,c,x);
x-=2.09;
}
}
for(r=0;r<matrix_rows;r++)
{
for(c=0;c<matrix_columns;c++)
{
value=mlearning_mat_double_get(matrix,r,c);
printf("%lf ",value);
}
printf("\n");
}
r=0;
c=0;
min=mlearning_mat_double_get_minimum(matrix,r,c,matrix_rows,matrix_columns);
printf("Minimum value is %lf\n",min);
return 0;
}