#ifndef __M__LEARNING__LIN__REG__
#define __M__LEARNING__LIN__REG__
#include<inttypes.h>
#include<mlearning_matrix.h>
#include<mlearning_vector.h>
mlearning_row_vec_double* mlearning_lin_reg_gd_fit_line(mlearning_mat_double*input_features_matrix,mlearning_column_vec_double*actual_values_vector,double learning_rate,uint64_t number_of_iterations,int (*iterate)(uint64_t iteration_number,double error_value));
mlearning_column_vec_double* mlearning_lin_reg_predict(mlearning_mat_double*input_features_matrix,mlearning_row_vec_double*trained_parameters);
#endif