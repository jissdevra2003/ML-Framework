#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<stdio.h>
#include<stdlib.h>

void score_it(char*results_file_name)
{
mlearning_mat_double*dataset;
dimension_t dataset_rows,dataset_columns;

double SSR;
double SST;
double r2score;
mlearning_column_vec_double*A;
mlearning_column_vec_double*P;
mlearning_column_vec_double*R; //A-P
mlearning_row_vec_double*RT; //R transpose
mlearning_column_vec_double*RTR; //RT*R
mlearning_column_vec_double*M;
double mean_of_actuals;
mlearning_column_vec_double*AM; //A-M
mlearning_row_vec_double*AMT; //AM transpose
mlearning_column_vec_double*AMTAM; //AMT*AM




dataset=mlearning_mat_double_from_csv(results_file_name);
if(dataset==NULL)
{
printf("Low memory\n");
return;
}
mlearning_mat_double_get_dimensions(dataset,&dataset_rows,&dataset_columns);

A=mlearning_mat_double_create_column_vec(dataset,dataset_columns-2); //2nd last column of dataset(Actual output)
if(A==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
return;
}
P=mlearning_mat_double_create_column_vec(dataset,dataset_columns-1); //last column of dataset(Predicted output)
if(P==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
return;
}

R=mlearning_subtract_double_column_vector(A,P);
if(R==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
return;
}

RT=mlearning_column_vec_double_transpose(R);
if(RT==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
return;
}

RTR=mlearning_multiply_double_row_vector_with_column_vector(RT,R);
if(RTR==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
return;
}

SSR=mlearning_column_vec_double_get(RTR,0);

mean_of_actuals=mlearning_column_vec_double_get_mean(A);

M=mlearning_column_vec_double_create_new_filled(dataset_rows,mean_of_actuals);
if(M==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
return;
}

AM=mlearning_subtract_double_column_vector(A,M);
if(AM==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
return;
}

AMT=mlearning_column_vec_double_transpose(AM);
if(AMT==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
return;
}

AMTAM=mlearning_multiply_double_row_vector_with_column_vector(AMT,AM);
if(AMTAM==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
mlearning_row_vec_double_destroy(AMT);
return;
}
SST=mlearning_column_vec_double_get(AMTAM,0);

r2score=1-(SSR/SST);
printf("R2score of the test is %lf\n",r2score);



mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
mlearning_row_vec_double_destroy(AMT);
mlearning_column_vec_double_destroy(AMTAM);
}

int main(int argc,char*argv[])
{
if(argc!=2)
{
printf("Usage : score_it.exe _ results_file_name\n");
return 0;
}
score_it(argv[1]);
return 0;
}