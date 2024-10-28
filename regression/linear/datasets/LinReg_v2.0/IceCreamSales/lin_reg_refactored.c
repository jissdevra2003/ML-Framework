#include<mlearning_learn.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
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
DWORD thread_id;
DWORD exit_code;
HANDLE thread_handle;
char m;
thread_args args_values;
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
if(argc<2)
{
args_values.number_of_iterations=0;
//printf("Specify the number of iterations as command line argument.");
//return 0;
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

args_values.matrix=training_data_matrix;
args_values.actual_values_vector=training_data_actual_values_vector;
args_values.learning_rate=0.0003;
if(argc==2)
{
args_values.number_of_iterations=atoi(argv[1]);
}
args_values.check_iteration=screen_logger;
thread_handle=CreateThread(NULL,0,thread_function,(void*)&args_values,0,&thread_id);
//pthread_create(&thread_id,NULL,thread_function,(void*)&args_values);

while(1)
{
m=getchar();
fflush(stdin);
if(m=='\n')   //enter key pressed so break from the loop
{
KEEP_RUNNING=0;
break;
}
}
WaitForSingleObject(thread_handle,INFINITE);
GetExitCodeThread(thread_handle,&exit_code);
trained_parameters=(mlearning_row_vec_double*)exit_code;
//pthread_join(thread_id,(void**)&trained_parameters); 
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