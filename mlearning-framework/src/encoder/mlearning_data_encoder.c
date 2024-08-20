#include<mlearning_set.h>
#include<mlearning_matrix.h>
#include<mlearning_encoder.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void mlearning_encoder_encode_one_hot(char*source,char*target,int*encode_columns,int size,int header_exists)
{
mlearning_mat_string*matrix;
mlearning_set_string**sets;
FILE*target_file;
char*set_string;
index_t i,j,c,r;
index_t data_start_row_index;
char *string;
dimension_t matrix_rows,matrix_columns;
dimension_t set_size;

if(source==NULL || target==NULL || size<=0 || encode_columns==NULL) return;

matrix=mlearning_mat_string_from_csv(source);
if(matrix==NULL) return;
mlearning_mat_string_get_dimensions(matrix,&matrix_rows,&matrix_columns);
for(i=0;i<size;i++)
{
c=encode_columns[i];
if(c<0 || c>=matrix_columns)
{
mlearning_mat_string_destroy(matrix);
}
}
sets=(mlearning_set_string**)malloc(sizeof(mlearning_set_string*)*size);
if(sets==NULL)
{
mlearning_mat_string_destroy(matrix);
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
return;
}
}
if(header_exists) data_start_row_index=1;
else data_start_row_index=0;

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
return;
}
free(string);
}
}
}

target_file=fopen(target,"w");
if(target_file==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
return;
}

if(header_exists)
{
for(c=0;c<matrix_columns;c++)
{
mlearning_mat_string_get(matrix,0,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) mlearning_set_string_destroy(sets[i]);
free(sets);
mlearning_mat_string_destroy(matrix);
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

}

