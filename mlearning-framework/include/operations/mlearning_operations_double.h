#ifndef __M__LEARNING__OPERATIONS__DOUBLE__
#define __M__LEARNING__OPERATIONS__DOUBLE__
mlearning_column_vec_double*mlearning_multiply_double_row_vector_with_column_vector(mlearning_row_vec_double*left_vector,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*product_vector);
mlearning_column_vec_double*mlearning_multiply_double_matrix_with_column_vector(mlearning_mat_double*left_matrix,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*product_vector);
mlearning_column_vec_double*mlearning_subtract_double_column_vector(mlearning_column_vec_double*left_vector,mlearning_column_vec_double*right_vector,mlearning_column_vec_double*difference_vector);
mlearning_column_vec_double*mlearning_multiply_double_scalar_with_column_vector(double scalar_value,mlearning_column_vec_double*vector,mlearning_column_vec_double*product_vector);
#endif