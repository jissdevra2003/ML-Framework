#ifndef __M__LEARNING__SET__STRING__
#define __M__LEARNING__SET__STRING__
struct __mlearning_set_string;
typedef struct __mlearning_set_string mlearning_set_string;

void mlearning_set_string_destroy(mlearning_set_string * set);
mlearning_set_string * mlearning_set_string_create_new();
mlearning_set_string * mlearning_set_string_from_csv(const char* csv_file_name);
//return -1 in case of low memory or 0 incase of added or not added because of duplicate
int mlearning_set_string_add(mlearning_set_string*set,char*string);
void mlearning_set_string_get(mlearning_set_string*set,index_t index,char**string);
dimension_t mlearning_set_string_get_size(mlearning_set_string*matrix);
#endif
