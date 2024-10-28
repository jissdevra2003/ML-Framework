#include<mlearning_learn.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_encoder.h>
#include<mlearning_scale.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

uint8_t KEEP_RUNNING=1;
typedef struct thread_args
{
mlearning_mat_double*matrix;
mlearning_column_vec_double*actual_values_vector;
double learning_rate;
uint64_t number_of_iterations;
int (*check_iteration)(uint64_t,double);
}thread_args;

//thread function
DWORD WINAPI thread_function(LPVOID lptr)
{
mlearning_row_vec_double*trained_parameters;
thread_args *t_args;
t_args=(thread_args*)lptr;

trained_parameters=mlearning_lin_reg_gd_fit_line(t_args->matrix,t_args->actual_values_vector,t_args->learning_rate,t_args->number_of_iterations,t_args->check_iteration);
Sleep(2000); //sleep for 2 seconds (2000 ms)

return (DWORD)trained_parameters;

}


int screen_logger(uint64_t iteration_number,double error_value)
{
printf("Iteration :%" PRIu64 ", Error :%40.15lf\n",iteration_number,error_value);
return KEEP_RUNNING;
}
int main(int argc,char*argv[])
{
DWORD thread_id,exit_code;
HANDLE thread_handle;
char m;
mlearning_row_vec_double*trained_parameters;
mlearning_row_vec_string*matrix_header;
dimension_t trained_parameters_size;
mlearning_mat_double*scaled_matrix;
mlearning_row_vec_string*columns_to_scale;


mlearning_mat_double*training_data_matrix;
mlearning_mat_double*testing_data_matrix;
dimension_t testing_mat_rows,testing_mat_columns;
mlearning_column_vec_double*testing_data_actual_values_vector;
mlearning_column_vec_double*training_data_actual_values_vector;
mlearning_column_vec_double*testing_data_predicted_values_vector;
dimension_t training_mat_rows,training_mat_columns;
index_t i;
double r2score;
thread_args args_values;
mlearning_row_vec_string*encode_columns_vector;
if(argc<2)
{
args_values.number_of_iterations=0;
// printf("Specify the number of iterations as command line argument.");
// return 0;
}
//encode data
encode_columns_vector=mlearning_row_vec_string_create_new(3);
if(encode_columns_vector==NULL) return 0;
mlearning_row_vec_string_set(encode_columns_vector,0,"sex");
mlearning_row_vec_string_set(encode_columns_vector,1,"smoker");
mlearning_row_vec_string_set(encode_columns_vector,2,"region");
mlearning_encoder_encode("insurance.csv","binary_encoded_insurance.csv",encode_columns_vector,"binary");


//encoding of data ends here 

//scaling of the data starts here
columns_to_scale=mlearning_row_vec_string_create_new(8);

if(columns_to_scale==NULL)
{
printf("Low memory\n");
return 0;
}
//columns name from binary_encoded_insurance.csv
mlearning_row_vec_string_set(columns_to_scale,0,"age");
mlearning_row_vec_string_set(columns_to_scale,1,"sex_1");
mlearning_row_vec_string_set(columns_to_scale,2,"bmi");
mlearning_row_vec_string_set(columns_to_scale,3,"children");
mlearning_row_vec_string_set(columns_to_scale,4,"smoker_1");
mlearning_row_vec_string_set(columns_to_scale,5,"region_1");
mlearning_row_vec_string_set(columns_to_scale,6,"region_2");
mlearning_row_vec_string_set(columns_to_scale,7,"charges");





scaled_matrix=mlearning_scale_double("binary_encoded_insurance.csv",columns_to_scale,"mean_standard_deviation.csv","z-score",NULL);
if(scaled_matrix==NULL)
{
printf("Unable to load scaled data\n");
mlearning_row_vec_string_destroy(columns_to_scale);
return 0;
}
matrix_header=mlearning_row_vec_string_create_new(8);
if(matrix_header==NULL)
{
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_mat_double_destroy(scaled_matrix);
printf("Low memory\n");
return 0;
}
mlearning_row_vec_string_set(matrix_header,0,"age");
mlearning_row_vec_string_set(matrix_header,1,"sex_1");
mlearning_row_vec_string_set(matrix_header,2,"bmi");
mlearning_row_vec_string_set(matrix_header,3,"children");
mlearning_row_vec_string_set(matrix_header,4,"smoker_1");
mlearning_row_vec_string_set(matrix_header,5,"region_1");
mlearning_row_vec_string_set(matrix_header,6,"region_2");
mlearning_row_vec_string_set(matrix_header,7,"charges");

mlearning_mat_double_to_csv(scaled_matrix,"scaled_insurance_data.csv",matrix_header);
mlearning_row_vec_string_destroy(columns_to_scale);
mlearning_mat_double_destroy(scaled_matrix);
mlearning_row_vec_string_destroy(matrix_header);

//scaling of data ends here


mlearning_mat_double_load_training_testing_data("scaled_insurance_data.csv",&training_data_matrix,&testing_data_matrix,30);
if(training_data_matrix==NULL)
{
printf("Unable to load training testing data\n");
return 0;
}
// matrix=mlearning_mat_double_from_csv("binary_encoded_insurance.csv",NULL,&matrix_header);
// if(matrix==NULL)
// {
// printf("Unable to load file\n");
// return 0;
// }
// mlearning_mat_double_get_dimensions(matrix,&matrix_rows,&matrix_columns);
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

args_values.matrix=training_data_matrix;
args_values.actual_values_vector=training_data_actual_values_vector;
args_values.learning_rate=0.0003;
if(argc==2)
{
args_values.number_of_iterations=atoi(argv[1]);
}
args_values.check_iteration=screen_logger;
thread_handle=CreateThread(NULL,0,thread_function,(void*)&args_values,0,&thread_id);

while(1)
{
m=getchar();
fflush(stdin);
if(m=='\n')
{
KEEP_RUNNING=0;
break;
}
}
WaitForSingleObject(thread_handle,INFINITE);
GetExitCodeThread(thread_handle,&exit_code);
trained_parameters=(mlearning_row_vec_double*)exit_code;
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


//test r2score
r2score=mlearning_compute_r2_score(testing_data_actual_values_vector,testing_data_predicted_values_vector);
printf("\nR2Score of the test is :%lf",r2score);


mlearning_mat_double_destroy(testing_data_matrix);
mlearning_column_vec_double_destroy(testing_data_actual_values_vector);
mlearning_column_vec_double_destroy(testing_data_predicted_values_vector);
mlearning_row_vec_double_destroy(trained_parameters);

return 0;
}