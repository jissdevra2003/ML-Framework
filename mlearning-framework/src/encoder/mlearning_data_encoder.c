#include<mlearning_set.h>
#include<mlearning_matrix.h>
#include<mlearning_encoder.h>
#include<mlearning_utils.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void mlearning_encoder_encode_one_hot(char*source,char*target,mlearning_row_vec_string*encode_columns_vector)
{
int*encode_columns;
dimension_t size;
char *ptr1,*ptr2;
mlearning_mat_string*matrix;
mlearning_set_string**sets;
FILE*target_file;
char*set_string;
index_t i,j,c,r;
int found;
dimension_t header_size;
index_t data_start_row_index;
mlearning_row_vec_string*header;
char *string;
dimension_t matrix_rows,matrix_columns;
dimension_t set_size;

if(source==NULL || target==NULL || encode_columns_vector==NULL) return;

matrix=mlearning_mat_string_from_csv(source,NULL,&header);  //actual header from the csv file
if(matrix==NULL) return;

//creating array of indexes ,encode_columns
size=mlearning_row_vec_string_get_size(encode_columns_vector);
encode_columns=(int*)malloc(sizeof(int)*size);
if(encode_columns==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
return;
}
header_size=mlearning_row_vec_string_get_size(header);

for(i=0;i<size;i++)
{
mlearning_row_vec_string_get(encode_columns_vector,i,&ptr1);
if(ptr1==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
found=0;

for(j=0;j<header_size;j++)
{
mlearning_row_vec_string_get(header,j,&ptr2);
if(ptr2==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
if(mlearning_string_equals_ignore_case(ptr1,ptr2)==0)
{
found=1;
}
free(ptr2);
if(found==1) break;
}
free(ptr1);
if(found==0)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
encode_columns[i]=j;
}



mlearning_mat_string_get_dimensions(matrix,&matrix_rows,&matrix_columns);
for(i=0;i<size;i++)
{
c=encode_columns[i];
if(c<0 || c>=matrix_columns)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}
sets=(mlearning_set_string**)malloc(sizeof(mlearning_set_string*)*size);
if(sets==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
for(i=0;i<size;i++)
{
sets[i]=mlearning_set_string_create_new();
if(sets[i]==NULL)
{
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}
data_start_row_index=0;

for(r=data_start_row_index;r<matrix_rows;r++)
{
for(i=0;i<size;i++)
{
c=encode_columns[i];
mlearning_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
else 
{
if(mlearning_set_string_add(sets[i],string)==-1)
{
free(string);
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
free(string);
}
}
}

//logic to write the target file
target_file=fopen(target,"w");
if(target_file==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}

for(c=0;c<header_size;c++)
{
mlearning_row_vec_string_get(header,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
return;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size) //found the cth column that has to be encoded
{
set_size=mlearning_set_string_get_size(sets[i]);
for(j=0;j<set_size;j++)
{
mlearning_set_string_get(sets[i],j,&set_string);
if(set_string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");  //create blank file and destroy
fclose(target_file);
return;
}
fputs(string,target_file);
fputc('_',target_file);
fputs(set_string,target_file);
free(set_string);
if(j<set_size-1) fputc(',',target_file);
}
}
else 
{
fputs(string,target_file);
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}

for(r=data_start_row_index;r<matrix_rows;r++)
{
for(c=0;c<matrix_columns;c++)
{
mlearning_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size)
{
set_size=mlearning_set_string_get_size(sets[i]);
for(j=0;j<set_size;j++)
{
mlearning_set_string_get(sets[i],j,&set_string);
if(set_string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return;
}
if(strcmp(string,set_string)==0)
{
fputc('1',target_file);
}
else
{
fputc('0',target_file);
} 
free(set_string);
if(j<set_size-1) fputc(',',target_file);
}
}
else 
{
fputs(string,target_file);
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}


}
fclose(target_file);
//code to test one hot encoding
// for(i=0;i<size;i++)
// {
// set_size=mlearning_set_string_get_size(sets[i]);
// for(j=0;j<set_size;j++)
// {
// mlearning_set_string_get(sets[i],j,&string);
// if(string!=NULL)
// {
// printf("%s\n",string);
// free(string);
// }
// }
// }
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
}

void mlearning_encoder_encode_to_binary(char*source,char*target,mlearning_row_vec_string*encode_columns_vector)
{
int*encode_columns;
dimension_t size;
char *ptr1,*ptr2;
index_t b_index;
int bits_required;
char b_string[33]; //+1 for '\0'
uint32_t largest_code;
char set_file_name[1507];
FILE*set_file;
mlearning_mat_string*matrix;
mlearning_set_string**sets;
FILE*target_file;
char*set_string;
index_t i,j,c,r;
int found;
dimension_t header_size;
index_t data_start_row_index;
mlearning_row_vec_string*header;
char *string;
dimension_t matrix_rows,matrix_columns;
dimension_t set_size;

if(source==NULL || target==NULL || encode_columns_vector==NULL) return;

matrix=mlearning_mat_string_from_csv(source,NULL,&header);  //actual header from the csv file
if(matrix==NULL) return;

//creating array of indexes encode_columns
size=mlearning_row_vec_string_get_size(encode_columns_vector);
encode_columns=(int*)malloc(sizeof(int)*size);
if(encode_columns==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
return;
}
header_size=mlearning_row_vec_string_get_size(header);

for(i=0;i<size;i++)
{
mlearning_row_vec_string_get(encode_columns_vector,i,&ptr1);
if(ptr1==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
found=0;

for(j=0;j<header_size;j++)
{
mlearning_row_vec_string_get(header,j,&ptr2);
if(ptr2==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
if(mlearning_string_equals_ignore_case(ptr1,ptr2)==0)
{
found=1;
}
free(ptr2);
if(found==1) break;
}
free(ptr1);
if(found==0)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
encode_columns[i]=j;
}



mlearning_mat_string_get_dimensions(matrix,&matrix_rows,&matrix_columns);
for(i=0;i<size;i++)
{
c=encode_columns[i];
if(c<0 || c>=matrix_columns)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}
sets=(mlearning_set_string**)malloc(sizeof(mlearning_set_string*)*size);
if(sets==NULL)
{
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
for(i=0;i<size;i++)
{
sets[i]=mlearning_set_string_create_new();
if(sets[i]==NULL)
{
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
}
data_start_row_index=0;

for(r=data_start_row_index;r<matrix_rows;r++)
{
for(i=0;i<size;i++)
{
c=encode_columns[i];
mlearning_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
else 
{
if(mlearning_set_string_add(sets[i],string)==-1)
{
free(string);
for(j=0;j<size;j++)
{
mlearning_set_string_destroy(sets[j]);
}
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}
free(string);
}
}
}

//logic to write the target file
target_file=fopen(target,"w");
if(target_file==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
return;
}

for(c=0;c<header_size;c++)
{
mlearning_row_vec_string_get(header,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
return;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size) //found the cth column that has to be encoded
{
set_size=mlearning_set_string_get_size(sets[i]);
largest_code=set_size-1;
mlearning_number_to_binary_string(largest_code,b_string);
for(b_index=0;b_string[b_index]=='0';b_index++);
bits_required=32-b_index;
for(b_index=1;b_index<=bits_required;b_index++)
{
fputs(string,target_file);
fputc('_',target_file);
fputc(b_index+48,target_file);
if(b_index<bits_required) fputc(',',target_file);
}
}
else 
{
fputs(string,target_file);
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}


for(r=data_start_row_index;r<matrix_rows;r++)
{
for(c=0;c<matrix_columns;c++)
{
mlearning_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return;
}
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i<size)
{
set_size=mlearning_set_string_get_size(sets[i]);
largest_code=set_size-1;
mlearning_number_to_binary_string(largest_code,b_string);
for(b_index=0;b_string[b_index]=='0';b_index++);
bits_required=32-b_index;
for(j=0;j<set_size;j++)
{
mlearning_set_string_get(sets[i],j,&set_string);
if(set_string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);
fclose(target_file);
target_file=fopen(target,"w");
fclose(target_file);
return;
}
if(strcmp(string,set_string)==0)
{
mlearning_number_to_binary_string(j,b_string);

for(b_index=32-bits_required;b_index<=31;b_index++)
{
fputc(b_string[b_index],target_file);
if(b_index<31) fputc(',',target_file);
}

free(set_string);
break;
}
free(set_string);
}
}
else 
{
fputs(string,target_file);
}
free(string);
if(c==matrix_columns-1) fputc('\n',target_file);
else fputc(',',target_file);
}


}

for(c=0;c<header_size;c++)
{
for(i=0;i<size;i++)
{
if(c==encode_columns[i]) break;
}
if(i==size) continue; //not found the column to encode
//found now create a file with header[c] and fill sets[i] string with code
mlearning_row_vec_string_get(header,c,&string);
if(string!=NULL)
{
sprintf(set_file_name,"%s.csv",string);
free(string);
set_file=fopen(set_file_name,"w");
if(set_file==NULL) free(string);
if(set_file!=NULL)
{
fprintf(set_file,"%s,code\n",string);
free(string);
set_size=mlearning_set_string_get_size(sets[i]);
for(j=0;j<set_size;j++)
{
mlearning_set_string_get(sets[i],j,&set_string);
if(set_string!=NULL)
{
fprintf(set_file,"%s,%d\n",set_string,j);
free(set_string);
}
}
fclose(set_file);
}
}
}
fclose(target_file);


for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
mlearning_row_vec_string_destroy(header);
free(encode_columns);

}

void mlearning_encoder_encode(char*source,char*target,mlearning_row_vec_string*encode_columns_vector,char*algorithm)
{
int algorithm_code;
int ONE_HOT_ENCODE=1;
int BINARY_ENCODE=2;
if(source==NULL || target==NULL || encode_columns_vector==NULL || algorithm==NULL) return;
if(mlearning_string_equals_ignore_case(algorithm,"one-hot")==0)
{
algorithm_code=ONE_HOT_ENCODE;
}
else if(mlearning_string_equals_ignore_case(algorithm,"binary")==0)
{
algorithm_code=BINARY_ENCODE;
}
else 
{
return;
}

if(algorithm_code==ONE_HOT_ENCODE)
{
mlearning_encoder_encode_one_hot(source,target,encode_columns_vector);
}
else if(algorithm_code==BINARY_ENCODE)
{
mlearning_encoder_encode_to_binary(source,target,encode_columns_vector);
}
}


