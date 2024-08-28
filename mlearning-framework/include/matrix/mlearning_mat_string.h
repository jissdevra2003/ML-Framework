#ifndef __M__LEARNING__MAT__STRING__
#define __M__LEARNING__MAT__STRING__
struct __mlearning_mat_string;
typedef struct __mlearning_mat_string mlearning_mat_string;

void mlearning_mat_string_destroy(mlearning_mat_string * matrix);
mlearning_mat_string * mlearning_mat_string_create_new(dimension_t rows,dimension_t columns);
mlearning_mat_string * mlearning_mat_string_from_csv(const char* csv_file_name);
void mlearning_mat_string_to_csv(mlearning_mat_string*matrix,const char*csv_file_name);
void mlearning_mat_string_set(mlearning_mat_string*matrix,index_t row,index_t column,char*string);
void mlearning_mat_string_get(mlearning_mat_string*matrix,index_t row,index_t column,char**string);
void mlearning_mat_string_get_dimensions(mlearning_mat_string*matrix,dimension_t *rows,dimension_t *columns);
#endif