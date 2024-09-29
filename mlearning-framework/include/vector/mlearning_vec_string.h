#ifndef __M__LEARNING__VEC__STRING__
#define __M__LEARNING__VEC__STRING__
struct __mlearning_row_vec_string;
struct __mlearning_column_vec_string;
typedef struct __mlearning_row_vec_string mlearning_row_vec_string;
typedef struct __mlearning_column_vec_string mlearning_column_vec_string;

//row functions
void mlearning_row_vec_string_destroy(mlearning_row_vec_string * vector);
mlearning_row_vec_string * mlearning_row_vec_string_create_new(dimension_t size);
<<<<<<< HEAD
mlearning_row_vec_string * mlearning_row_vec_string_from_csv(const char* csv_file_name,mlearning_row_vec_string*vector,mlearning_row_vec_string**header);
void mlearning_row_vec_string_to_csv(mlearning_row_vec_string*vector,const char*csv_file_name,mlearning_row_vec_string*header);
void mlearning_row_vec_string_set(mlearning_row_vec_string*vector,index_t index,char*string);
void mlearning_row_vec_string_get(mlearning_row_vec_string*vector,index_t index,char**string);
dimension_t mlearning_row_vec_string_get_size(mlearning_row_vec_string*vector);
mlearning_column_vec_string*mlearning_row_vec_string_transpose(mlearning_row_vec_string*vector,mlearning_column_vec_string*transposed_vector);
=======
mlearning_row_vec_string * mlearning_row_vec_string_from_csv(const char* csv_file_name);
void mlearning_row_vec_string_to_csv(mlearning_row_vec_string*vector,const char*csv_file_name);
void mlearning_row_vec_string_set(mlearning_row_vec_string*vector,index_t index,char*string);
void mlearning_row_vec_string_get(mlearning_row_vec_string*vector,index_t index,char**string);
dimension_t mlearning_row_vec_string_get_size(mlearning_row_vec_string*vector);
mlearning_column_vec_string*mlearning_row_vec_string_transpose(mlearning_row_vec_string*vector);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca

//column functions
void mlearning_column_vec_string_destroy(mlearning_column_vec_string * vector);
mlearning_column_vec_string * mlearning_column_vec_string_create_new(dimension_t size);
<<<<<<< HEAD
mlearning_column_vec_string * mlearning_column_vec_string_from_csv(const char* csv_file_name,mlearning_column_vec_string*vector,mlearning_row_vec_string**header);
void mlearning_column_vec_string_to_csv(mlearning_column_vec_string*vector,const char*csv_file_name,mlearning_row_vec_string*header);
void mlearning_column_vec_string_set(mlearning_column_vec_string*vector,index_t index,char*string);
void mlearning_column_vec_string_get(mlearning_column_vec_string*vector,index_t index,char**string);
dimension_t mlearning_column_vec_string_get_size(mlearning_column_vec_string*vector);
mlearning_row_vec_string*mlearning_column_vec_string_transpose(mlearning_column_vec_string*vector,mlearning_row_vec_string*transposed_vector);
=======
mlearning_column_vec_string * mlearning_column_vec_string_from_csv(const char* csv_file_name);
void mlearning_column_vec_string_to_csv(mlearning_column_vec_string*vector,const char*csv_file_name);
void mlearning_column_vec_string_set(mlearning_column_vec_string*vector,index_t index,char*string);
void mlearning_column_vec_string_get(mlearning_column_vec_string*vector,index_t index,char**string);
dimension_t mlearning_column_vec_string_get_size(mlearning_column_vec_string*vector);
mlearning_row_vec_string*mlearning_column_vec_string_transpose(mlearning_column_vec_string*vector);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca

#endif