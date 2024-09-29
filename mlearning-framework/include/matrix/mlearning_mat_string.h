#ifndef __M__LEARNING__MAT__STRING__
#define __M__LEARNING__MAT__STRING__
struct __mlearning_mat_string;
typedef struct __mlearning_mat_string mlearning_mat_string;

void mlearning_mat_string_destroy(mlearning_mat_string * matrix);
mlearning_mat_string * mlearning_mat_string_create_new(dimension_t rows,dimension_t columns);
<<<<<<< HEAD
mlearning_mat_string * mlearning_mat_string_from_csv(const char* csv_file_name,mlearning_mat_string*matrix,mlearning_row_vec_string**header);
void mlearning_mat_string_to_csv(mlearning_mat_string*matrix,const char*csv_file_name,mlearning_row_vec_string*header);
void mlearning_mat_string_set(mlearning_mat_string*matrix,index_t row,index_t column,char*string);
void mlearning_mat_string_get(mlearning_mat_string*matrix,index_t row,index_t column,char**string);
void mlearning_mat_string_get_dimensions(mlearning_mat_string*matrix,dimension_t *rows,dimension_t *columns);
mlearning_mat_string*mlearning_mat_string_transpose(mlearning_mat_string*matrix,mlearning_mat_string*transposed_matrix);
void mlearning_mat_string_copy(mlearning_mat_string*target,mlearning_mat_string*source,index_t target_row_index,index_t target_column_index,index_t source_from_row_index,index_t source_from_column_index,index_t source_to_row_index,index_t source_to_column_index);
mlearning_mat_string* mlearning_mat_string_shuffle(mlearning_mat_string*matrix,uint8_t shuffle_count,mlearning_mat_string*shuffled_matrix);
=======
mlearning_mat_string * mlearning_mat_string_from_csv(const char* csv_file_name);
void mlearning_mat_string_to_csv(mlearning_mat_string*matrix,const char*csv_file_name);
void mlearning_mat_string_set(mlearning_mat_string*matrix,index_t row,index_t column,char*string);
void mlearning_mat_string_get(mlearning_mat_string*matrix,index_t row,index_t column,char**string);
void mlearning_mat_string_get_dimensions(mlearning_mat_string*matrix,dimension_t *rows,dimension_t *columns);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
#endif