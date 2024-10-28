#include<mlearning_vector.h>
#include<mlearning_matrix.h>
#include<mlearning_learn.h>
#include<mlearning_operations.h>
#include<stdio.h>
mlearning_row_vec_double* mlearning_lin_reg_gd_fit_line(mlearning_mat_double*input_features_matrix,mlearning_column_vec_double*actual_values_vector,double learning_rate,uint64_t number_of_iterations,int (*iteration)(uint64_t iteration_number,double error_value))
{
int error_flag;
index_t r;
mlearning_mat_double*I;
dimension_t I_rows,I_columns;
dimension_t P_vector_size;
dimension_t E_vector_size;
mlearning_column_vec_double*A;
mlearning_column_vec_double*P;
mlearning_column_vec_double*m;
mlearning_column_vec_double*E;
mlearning_row_vec_double*ET;
mlearning_column_vec_double*ETE;
mlearning_column_vec_double*UM;
mlearning_mat_double*IT;
mlearning_column_vec_double*ITE;
mlearning_column_vec_double*TMP;
mlearning_row_vec_double*trained_parameters;
uint64_t k;
double sum_of_squared_error_values;
double final_error_value;
if(input_features_matrix==NULL || actual_values_vector==NULL) return NULL;
if(number_of_iterations==0 && iteration==NULL) return NULL;
I=input_features_matrix;
mlearning_mat_double_get_dimensions(I,&I_rows,&I_columns);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns+1);
if(I==NULL)
{
return NULL;
}
I_columns++;
mlearning_mat_double_right_shift_matrix_cols(I,1);
mlearning_mat_double_fill(I,0,0,I_rows-1,0,1.0);  //filled bias

IT=mlearning_mat_double_transpose(I,NULL);
if(IT==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
return NULL;
}

A=actual_values_vector;


m=mlearning_column_vec_double_create_new_filled(I_columns,0.0,NULL);  // 'm' column vector
if(m==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
return NULL;
}


P=mlearning_column_vec_double_create_new(I_rows);
if(P==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
return NULL;
}
P_vector_size=mlearning_column_vec_double_get_size(P);

E=mlearning_column_vec_double_create_new(P_vector_size);
if(E==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
return NULL;
}
E_vector_size=mlearning_column_vec_double_get_size(E);

ET=mlearning_row_vec_double_create_new(E_vector_size);
if(ET==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
return NULL;
}

ETE=mlearning_column_vec_double_create_new(1);
if(ETE==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
return NULL;
}

ITE=mlearning_column_vec_double_create_new(I_columns);
if(ITE==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
return NULL;

}

TMP=mlearning_column_vec_double_create_new(I_columns);
if(TMP==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
return NULL;
}

UM=mlearning_column_vec_double_create_new(I_columns);
if(UM==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_column_vec_double_destroy(TMP);
return NULL;
}

k=1;
error_flag=0;
while(1)
{
if(number_of_iterations>0 && k==(number_of_iterations+1)) break;
P=mlearning_multiply_double_matrix_with_column_vector(I,m,P);
if(P==NULL)
{
error_flag=1;
break;
}

E=mlearning_subtract_double_column_vector(P,A,E);
if(E==NULL)
{
error_flag=1;
break;
}

ET=mlearning_column_vec_double_transpose(E,ET);
if(ET==NULL)
{
error_flag=1;
break;
}

ETE=mlearning_multiply_double_row_vector_with_column_vector(ET,E,ETE);
if(ETE==NULL)
{
error_flag=1;
break;
}

sum_of_squared_error_values=mlearning_column_vec_double_get(ETE,0);
final_error_value=(sum_of_squared_error_values/(2*I_rows));

//logic to update m vector values
ITE=mlearning_multiply_double_matrix_with_column_vector(IT,E,ITE);
if(ITE==NULL)
{
error_flag=1;
break;
}

TMP=mlearning_multiply_double_scalar_with_column_vector((learning_rate*(1.0/I_rows)),ITE,TMP);
if(TMP==NULL)
{
error_flag=1;
break;
}

UM=mlearning_subtract_double_column_vector(m,TMP,UM);
if(UM==NULL)
{
error_flag=1;
break;
}

//set the updated values of m in m vector from UM vector

for(r=0;r<I_columns;r++)
{
mlearning_column_vec_double_set(m,r,mlearning_column_vec_double_get(UM,r));
}

//check for next iteration 
if(iteration!=NULL)
{
if(iteration(k,final_error_value)==0) break;   //calling the function for next iteration information 
}

k++;
}
if(error_flag==1)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(TMP);
mlearning_column_vec_double_destroy(UM);
mlearning_column_vec_double_destroy(m);
return NULL;
}
//release resources
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(TMP);
mlearning_column_vec_double_destroy(UM);

mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
trained_parameters=mlearning_column_vec_double_transpose(m,NULL);
mlearning_column_vec_double_destroy(m);
return trained_parameters;
}


mlearning_column_vec_double* mlearning_lin_reg_predict(mlearning_mat_double*input_features_matrix,mlearning_row_vec_double*trained_parameters)
{
//mlearning_column_vec_double*predicted_values_vector=P;
mlearning_mat_double*I;
dimension_t I_rows,I_columns;

mlearning_column_vec_double*m;
mlearning_column_vec_double*P;
dimension_t trained_para_size;
if(input_features_matrix==NULL || trained_parameters==NULL) return NULL;

trained_para_size=mlearning_row_vec_double_get_size(trained_parameters);
I=input_features_matrix;
mlearning_mat_double_get_dimensions(I,&I_rows,&I_columns);
if(trained_para_size!=I_columns+1) return NULL;
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns+1);
if(I==NULL)
{
return NULL;
}

I_columns++;

mlearning_mat_double_right_shift_matrix_cols(I,1); 
mlearning_mat_double_fill(I,0,0,I_rows-1,0,1.0);

m=mlearning_row_vec_double_transpose(trained_parameters,NULL);
if(m==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
return NULL;
}


P=mlearning_multiply_double_matrix_with_column_vector(I,m,NULL);
if(P==NULL)
{
mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_column_vec_double_destroy(m);
return NULL;
}

mlearning_mat_double_left_shift_matrix_cols(I,1);
mlearning_mat_double_reshape_matrix(&I,I_rows,I_columns-1);
mlearning_column_vec_double_destroy(m);
return P;
}
