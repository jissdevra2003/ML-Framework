#include<mlearning_learn.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<stdio.h>
#include<stdlib.h>

int screen_logger(uint64_t iteration_number,double error_value)
{
printf("Iteration :%" PRIu64 ", Error :%40.15lf\n",iteration_number,error_value);
return 1;
}
int main(int argc,char*argv[])
{
mlearning_mat_double*training_data_matrix;
mlearning_mat_double*testing_data_matrix;
dimension_t testing_mat_rows,testing_mat_columns;
mlearning_row_vec_double*trained_parameters;
mlearning_column_vec_double*testing_data_actual_values_vector;
mlearning_column_vec_double*training_data_actual_values_vector;
mlearning_column_vec_double*testing_data_predicted_values_vector;
dimension_t training_mat_rows,training_mat_columns;
dimension_t trained_parameters_size;
index_t i;
double r2score;
if(argc!=2)
{
printf("Specify the number of iterations as command line argument.");
return 0;
}

mlearning_mat_double_load_training_testing_data("IceCreamSales.csv",&training_data_matrix,&testing_data_matrix,30);
if(training_data_matrix==NULL)
{
printf("Unable to load training and testing matrices\n");
return 0;
}

mlearning_mat_double_get_dimensions(training_data_matrix,&training_mat_rows,&training_mat_columns);
mlearning_mat_double_get_dimensions(testing_data_matrix,&testing_mat_rows,&testing_mat_columns);

training_data_actual_values_vector=mlearning_mat_double_create_column_vec(training_data_matrix,training_mat_columns-1,NULL);
if(training_data_actual_values_vector==NULL)
{
printf("Low memory");
mlearning_mat_double_destroy(training_data_matrix);
mlearning_mat_double_destroy(testing_data_matrix);
return 0;
}

mlearning_mat_double_reshape_matrix(&training_data_matrix,training_mat_rows,training_mat_columns-1);
if(training_data_matrix==NULL)
{
printf("Low memory");
mlearning_column_vec_double_destroy(training_data_actual_values_vector);
mlearning_mat_double_destroy(testing_data_matrix);
return 0;
}
training_mat_columns--;
trained_parameters=mlearning_lin_reg_gd_fit_line(training_data_matrix,training_data_actual_values_vector,0.0001,atoi(argv[1]),screen_logger);
if(trained_parameters==NULL)
{
printf("Low memory");
mlearning_mat_double_destroy(training_data_matrix);
mlearning_column_vec_double_destroy(training_data_actual_values_vector);
mlearning_mat_double_destroy(testing_data_matrix);
return 0;
}
trained_parameters_size=mlearning_row_vec_double_get_size(trained_parameters);
printf("Trained parameters are :\n");
for(i=0;i<trained_parameters_size;i++)
{
printf("%lf ",mlearning_row_vec_double_get(trained_parameters,i));
}

mlearning_mat_double_destroy(training_data_matrix);
mlearning_column_vec_double_destroy(training_data_actual_values_vector);



testing_data_actual_values_vector=mlearning_mat_double_create_column_vec(testing_data_matrix,testing_mat_columns-1,NULL);
if(testing_data_actual_values_vector==NULL)
{
printf("Low memory");
mlearning_mat_double_destroy(testing_data_matrix);
mlearning_row_vec_double_destroy(trained_parameters);
return 0;
}

mlearning_mat_double_reshape_matrix(&testing_data_matrix,testing_mat_rows,testing_mat_columns-1);
if(testing_data_matrix==NULL)
{
printf("Low memory");
mlearning_row_vec_double_destroy(trained_parameters);
mlearning_column_vec_double_destroy(testing_data_actual_values_vector);
return 0;
}
testing_mat_columns--;
testing_data_predicted_values_vector=mlearning_lin_reg_predict(testing_data_matrix,trained_parameters);
if(testing_data_predicted_values_vector==NULL)
{
printf("Low memory");
mlearning_mat_double_destroy(testing_data_matrix);
mlearning_row_vec_double_destroy(trained_parameters);
mlearning_column_vec_double_destroy(testing_data_actual_values_vector);
return 0;
}

r2score=mlearning_compute_r2_score(testing_data_actual_values_vector,testing_data_predicted_values_vector);

printf("\nAccuracy score is :%lf\n",r2score);

mlearning_mat_double_destroy(testing_data_matrix);
mlearning_column_vec_double_destroy(testing_data_actual_values_vector);
mlearning_column_vec_double_destroy(testing_data_predicted_values_vector);
mlearning_row_vec_double_destroy(trained_parameters);
return 0;
}