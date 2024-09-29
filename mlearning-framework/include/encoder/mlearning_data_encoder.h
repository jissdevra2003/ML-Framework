#ifndef __M__LEARNING__DATA__ENCODER__
#define __M__LEARNING__DATA__ENCODER__
<<<<<<< HEAD
#include<mlearning_vector.h>
void mlearning_encoder_encode_one_hot(char*source,char*target,mlearning_row_vec_string*encode_columns_vector);
void mlearning_encoder_encode_to_binary(char*source,char*target,mlearning_row_vec_string*encode_columns_vector);
void mlearning_encoder_encode(char*source,char*target,mlearning_row_vec_string*encode_columns_vector,char*algorithm);
=======
void mlearning_encoder_encode_one_hot(char*source,char*target,int*encode_columns,int size,int header_exists);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca

#endif