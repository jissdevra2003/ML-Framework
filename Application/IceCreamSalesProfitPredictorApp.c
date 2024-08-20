#include<stdio.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
int main()
{
double temperature;
double temperature_f;
double prediction;
char*parameters_file_name="model.csv";
mlearning_column_vec_double*c_vector;
mlearning_row_vec_double*r_vector;
mlearning_column_vec_double*prediction_vector;
printf("Ice Cream Sales Profit Prediction Application\n\nProfit vision\n\n");
printf("Enter temperature :");
scanf("%lf",&temperature);
fflush(stdin);
temperature_f=(temperature*9.0/5.0)+32.0;
c_vector=mlearning_column_vec_double_from_csv(parameters_file_name);
if(c_vector==NULL)
{
printf("Low memory\n");
return 0;
}
r_vector=mlearning_row_vec_double_create_new(2);
if(r_vector==NULL)
{
mlearning_column_vec_double_destroy(c_vector);
return 0;
}
mlearning_row_vec_double_set(r_vector,0,1.0);
mlearning_row_vec_double_set(r_vector,1,temperature_f);

prediction_vector=mlearning_multiply_double_row_vector_with_column_vector(r_vector,c_vector);
if(prediction_vector==NULL)
{
mlearning_column_vec_double_destroy(c_vector);
mlearning_row_vec_double_destroy(r_vector);
return 0;
}
prediction=mlearning_column_vec_double_get(prediction_vector,0);
printf("\nPredicted profit in USD is :   %lf\n",prediction);
return 0;
}