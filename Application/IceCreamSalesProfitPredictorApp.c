#include<stdio.h>
#include<stdlib.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
int main(int argc,char*argv[])
{
double temperature;
double temperature_f;
double prediction;
mlearning_row_vec_string*header;
mlearning_row_vec_double*rr_vector;
FILE*parameters_file_name;
mlearning_column_vec_double*c_vector;
mlearning_row_vec_double*r_vector;
mlearning_column_vec_double*prediction_vector;
if(argc!=2)
{
fprintf(stderr,"Temperature not found");
return 0;
}
temperature=strtod(argv[1],NULL);
temperature_f=(temperature*9.0/5.0)+32.0;
parameters_file_name=fopen("ice_cream_sales_model.csv","r");
if(parameters_file_name==NULL)
{
fprintf(stderr,"Unable to load model.csv");
return 0;
}
rr_vector=mlearning_row_vec_double_from_csv("ice_cream_sales_model.csv",NULL,&header);
c_vector=mlearning_row_vec_double_transpose(rr_vector,NULL);
if(c_vector==NULL)
{
fprintf(stderr,"Lowww memory");
fclose(parameters_file_name);

return 0;
}
r_vector=mlearning_row_vec_double_create_new(2);
if(r_vector==NULL)
{
fprintf(stderr,"Low memory");
mlearning_column_vec_double_destroy(c_vector);
return 0;
}
mlearning_row_vec_double_set(r_vector,0,1.0);
mlearning_row_vec_double_set(r_vector,1,temperature_f);

prediction_vector=mlearning_multiply_double_row_vector_with_column_vector(r_vector,c_vector,NULL);
if(prediction_vector==NULL)
{
mlearning_column_vec_double_destroy(c_vector);
mlearning_row_vec_double_destroy(r_vector);
return 0;
}
prediction=mlearning_column_vec_double_get(prediction_vector,0);
printf("%lf",prediction);
fclose(parameters_file_name);
return 0;
}