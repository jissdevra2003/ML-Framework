#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<mlearning_learn.h>
#include<stdio.h>

double mlearning_compute_r2_score(mlearning_column_vec_double*actual_values_vec,mlearning_column_vec_double*predicted_values_vec)
{
mlearning_column_vec_double*A;
mlearning_column_vec_double*P;
mlearning_column_vec_double*R; //A-P
mlearning_row_vec_double*RT;
mlearning_column_vec_double*RTR;  //RT*R
mlearning_column_vec_double*M;
mlearning_column_vec_double*AM;
mlearning_row_vec_double*AMT;
mlearning_column_vec_double*AMTAM;
dimension_t actual_vec_size;
dimension_t pred_vec_size;
double SSR;
double SST;
double r2score;
double mean;
if(actual_values_vec==NULL || predicted_values_vec==NULL)
{
 return 0.0;
}
actual_vec_size=mlearning_column_vec_double_get_size(actual_values_vec);
pred_vec_size=mlearning_column_vec_double_get_size(predicted_values_vec);
if(actual_vec_size!=pred_vec_size) return 0.0;

A=actual_values_vec;
P=predicted_values_vec;

R=mlearning_subtract_double_column_vector(A,P,NULL);
if(R==NULL)
{
return 0.0;
}

RT=mlearning_column_vec_double_transpose(R,NULL);
if(RT==NULL)
{
mlearning_column_vec_double_destroy(R);
return 0.0;
}
RTR=mlearning_multiply_double_row_vector_with_column_vector(RT,R,NULL);
if(RTR==NULL)
{
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
return 0.0;
}
SSR=mlearning_column_vec_double_get(RTR,0);
mean=mlearning_column_vec_double_get_mean(A);
M=mlearning_column_vec_double_create_new_filled(actual_vec_size,mean,NULL);
if(M==NULL)
{
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
return 0.0;
}
AM=mlearning_subtract_double_column_vector(A,M,NULL);
if(AM==NULL)
{
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
return 0.0;
}
AMT=mlearning_column_vec_double_transpose(AM,NULL);
if(AMT==NULL)
{
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
return 0.0;
}

AMTAM=mlearning_multiply_double_row_vector_with_column_vector(AMT,AM,NULL);
if(AMTAM==NULL)
{
mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
mlearning_row_vec_double_destroy(AMT);
return 0.0;
}

SST=mlearning_column_vec_double_get(AMTAM,0);
r2score=1-(SSR/SST);

mlearning_column_vec_double_destroy(R);
mlearning_row_vec_double_destroy(RT);
mlearning_column_vec_double_destroy(RTR);
mlearning_column_vec_double_destroy(M);
mlearning_column_vec_double_destroy(AM);
mlearning_row_vec_double_destroy(AMT);
mlearning_column_vec_double_destroy(AMTAM);
return r2score;
}
