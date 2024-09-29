#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<stdio.h>
#include<stdlib.h>

void score_it(char*results_file_name)
{
mlearning_mat_double*dataset;
dimension_t dataset_rows,dataset_columns;
<<<<<<< HEAD
mlearning_row_vec_string*dataset_header;
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca

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




<<<<<<< HEAD
dataset=mlearning_mat_double_from_csv(results_file_name,NULL,&dataset_header);
=======
dataset=mlearning_mat_double_from_csv(results_file_name);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(dataset==NULL)
{
printf("Low memory\n");
return;
}
mlearning_mat_double_get_dimensions(dataset,&dataset_rows,&dataset_columns);

<<<<<<< HEAD
A=mlearning_mat_double_create_column_vec(dataset,dataset_columns-2,NULL); //2nd last column of dataset(Actual output)
=======
A=mlearning_mat_double_create_column_vec(dataset,dataset_columns-2); //2nd last column of dataset(Actual output)
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(A==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
return;
}
P=mlearning_mat_double_create_column_vec(dataset,dataset_columns-1,NULL); //last column of dataset(Predicted output)
=======
return;
}
P=mlearning_mat_double_create_column_vec(dataset,dataset_columns-1); //last column of dataset(Predicted output)
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(P==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
return;
}

R=mlearning_subtract_double_column_vector(A,P,NULL);
=======
return;
}

R=mlearning_subtract_double_column_vector(A,P);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(R==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
return;
}

RT=mlearning_column_vec_double_transpose(R,NULL);
=======
return;
}

RT=mlearning_column_vec_double_transpose(R);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(RT==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
return;
}

RTR=mlearning_multiply_double_row_vector_with_column_vector(RT,R,NULL);
=======
return;
}

RTR=mlearning_multiply_double_row_vector_with_column_vector(RT,R);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(RTR==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
return;
}

SSR=mlearning_column_vec_double_get(RTR,0);

mean_of_actuals=mlearning_column_vec_double_get_mean(A);

<<<<<<< HEAD
M=mlearning_column_vec_double_create_new_filled(dataset_rows,mean_of_actuals,NULL);
=======
M=mlearning_column_vec_double_create_new_filled(dataset_rows,mean_of_actuals);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(M==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
return;
}

<<<<<<< HEAD
AM=mlearning_subtract_double_column_vector(A,M,NULL);
=======
AM=mlearning_subtract_double_column_vector(A,M);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(AM==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
return;
}

<<<<<<< HEAD
AMT=mlearning_column_vec_double_transpose(AM,NULL);
=======
AMT=mlearning_column_vec_double_transpose(AM);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(AMT==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
return;
}

<<<<<<< HEAD
AMTAM=mlearning_multiply_double_row_vector_with_column_vector(AMT,AM,NULL);
=======
AMTAM=mlearning_multiply_double_row_vector_with_column_vector(AMT,AM);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(AMTAM==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
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
<<<<<<< HEAD
mlearning_row_vec_string_destroy(dataset_header);
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
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
<<<<<<< HEAD
printf("Usage : score_it _ results_file_name\n");
=======
printf("Usage : score_it.exe _ results_file_name\n");
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
return 0;
}
score_it(argv[1]);
return 0;
}