#ifndef __M__LEARNING__MAT__DOUBLE__
#define __M__LEARNING__MAT__DOUBLE__
struct __mlearning_mat_double;
typedef struct __mlearning_mat_double mlearning_mat_double;

void mlearning_mat_double_destroy(mlearning_mat_double * matrix);
mlearning_mat_double * mlearning_mat_double_create_new(dimension_t rows,dimension_t columns);
<<<<<<< HEAD
mlearning_mat_double * mlearning_mat_double_from_csv(const char* csv_file_name,mlearning_mat_double*matrix,mlearning_row_vec_string**header);
=======
mlearning_mat_double * mlearning_mat_double_from_csv(const char* csv_file_name,mlearning_mat_double*matrix);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
void mlearning_mat_double_set(mlearning_mat_double*matrix,index_t row,index_t column,double value);
double mlearning_mat_double_get(mlearning_mat_double*matrix,index_t row,index_t column);

void mlearning_mat_double_get_dimensions(mlearning_mat_double*matrix,dimension_t *rows,dimension_t *columns);
void mlearning_mat_double_copy(mlearning_mat_double*target_matrix,mlearning_mat_double*source_matrix,index_t target_row_index,index_t target_column_index,index_t source_from_row_index,index_t source_from_column_index,index_t source_to_row_index,index_t source_to_column_index);
void mlearning_mat_double_fill(mlearning_mat_double*matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value);

mlearning_column_vec_double*mlearning_mat_double_create_column_vec(mlearning_mat_double*matrix,index_t column_index,mlearning_column_vec_double*vector);

mlearning_mat_double* mlearning_mat_double_shuffle(mlearning_mat_double*matrix,uint8_t shuffle_count,mlearning_mat_double*shuffled_matrix);
<<<<<<< HEAD
void mlearning_mat_double_to_csv(mlearning_mat_double*matrix,char*csv_file_name,mlearning_row_vec_string*header);
=======
void mlearning_mat_double_to_csv(mlearning_mat_double*matrix,char*csv_file_name);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca

mlearning_mat_double*mlearning_mat_double_transpose(mlearning_mat_double*matrix,mlearning_mat_double*transposed_matrix);
double mlearning_mat_double_get_minimum(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);
double mlearning_mat_double_get_maximum(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);

<<<<<<< HEAD
double mlearning_mat_double_get_mean(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);
double mlearning_mat_double_get_standard_deviation(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);
void mlearning_mat_double_load_training_testing_data(char*csv_file_name,mlearning_mat_double**training_data,mlearning_mat_double**testing_data,uint8_t test_data_percentage);

=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
#endif