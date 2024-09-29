#include<mlearning_matrix.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct __mlearning_mat_string
{
char***data;
dimension_t rows;
dimension_t columns;
}mlearning_mat_string;

mlearning_mat_string * mlearning_mat_string_create_new(dimension_t rows,dimension_t columns)
{
mlearning_mat_string*matrix;
index_t r,c,k;
if(rows<=0 || columns<=0) return NULL;
matrix=(mlearning_mat_string*)malloc(sizeof(mlearning_mat_string));
if(matrix==NULL) return NULL;
matrix->data=(char***)malloc(sizeof(char**)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}

for(r=0;r<rows;r++)
{
matrix->data[r]=(char**)malloc(sizeof(char*)*columns);
if(matrix->data[r]==NULL)
{
for(k=0;k<r;k++)
{
free(matrix->data[k]);
}
free(matrix->data);
free(matrix);
return NULL;
}
else 
{
for(c=0;c<columns;c++)
{
matrix->data[r][c]=NULL;
}
}
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}

void mlearning_mat_string_destroy(mlearning_mat_string*matrix)
{
index_t r,c;
if(matrix==NULL) return;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
free(matrix->data[r][c]);
}
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
}

mlearning_mat_string * mlearning_mat_string_from_csv(const char*csv_file_name,mlearning_mat_string*matrix,mlearning_row_vec_string**header)
{
index_t r,c;
dimension_t header_size;
index_t header_index;
char header_string[1507];
dimension_t rows,columns;
char m;
int index;
char string[7021];
FILE*file;
if(csv_file_name==NULL || header==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;


//logic to read the header line from file
header_size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') header_size++;
if(m=='\n') break;
}
header_size++;  
*header=mlearning_row_vec_string_create_new(header_size);
if(*header==NULL) 
{
fclose(file);
return NULL;
}
rewind(file);
index=0;
header_index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
header_string[index]='\0';
index=0;
mlearning_row_vec_string_set(*header,header_index,header_string);
header_index++;
if(header_index==header_size) break;
}
else 
{
header_string[index]=m;
index++;
}
}
//logic to read the header line ends



rows=0;
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(rows==0)
{
if(m==',') columns++;
}
if(m=='\n') rows++;
}
columns++;
if(columns!=header_size)
{
mlearning_row_vec_string_destroy(*header);
fclose(file);
*header=NULL;
return NULL;
}
if(matrix==NULL)
{
matrix=mlearning_mat_string_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else 
{
if(matrix->rows!=rows || matrix->columns!=columns) 
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}


rewind(file);
//skip the first header line from file
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}

r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
string[index]='\0';
matrix->data[r][c]=(char*)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[r][c]!=NULL)
{
strcpy(matrix->data[r][c],string);
}
index=0;
c++;
if(c==matrix->columns)
{
r++;
c=0;
}
}
else
{
string[index]=m;
index++;
}
if(r==matrix->rows) break;
}
fclose(file);
return matrix;
}

void mlearning_mat_string_to_csv(mlearning_mat_string*matrix,const char*csv_file_name,mlearning_row_vec_string*header)
{
FILE*file;
dimension_t header_size;
index_t index;
char*ptr;
index_t r,c;
if(matrix==NULL) return;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
if(header_size!=matrix->columns) return;//header size should be equal to the columns in matrix
file=fopen(csv_file_name,"w");
if(file==NULL) return;




for(index=0;index<header_size;index++)
{
mlearning_row_vec_string_get(header,index,&ptr);
if(ptr!=NULL)
{
fputs(ptr,file);
free(ptr);
}
if(index<header_size-1) fputc(',',file);
else fputc('\n',file);
}



for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
if(matrix->data[r][c]!=NULL) fputs(matrix->data[r][c],file);
if(c<matrix->columns-1) fputc(',',file);
else fputc('\n',file);
}

}
fclose(file);

}

void mlearning_mat_string_get(mlearning_mat_string*matrix,index_t row,index_t column,char**string)
{
if(matrix==NULL) return;
if(string==NULL) return;
if(row<0 || row>=matrix->rows)
{
*string=NULL;
return;
}
if(column<0 || column>=matrix->columns)
{
*string=NULL;
return;
}
if(matrix->data[row][column]!=NULL)
{
*string=(char*)malloc(sizeof(char)*(strlen(matrix->data[row][column])+1));
strcpy(*string,matrix->data[row][column]);
}

}

void mlearning_mat_string_set(mlearning_mat_string*matrix,index_t row,index_t column,char*string)
{
if(matrix==NULL) return;
if(row<0 || row>=matrix->rows) return;
if(column<0 || column>=matrix->columns) return;
if(matrix->data[row][column]!=NULL) free(matrix->data[row][column]);
matrix->data[row][column]=(char*)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[row][column]!=NULL)
{
strcpy(matrix->data[row][column],string);
}
}
void mlearning_mat_string_get_dimensions(mlearning_mat_string*matrix,dimension_t *rows,dimension_t *columns)
{
if(matrix==NULL) return;
if(rows!=NULL)
{
*rows=matrix->rows;
}
if(columns!=NULL)
{
*columns=matrix->columns;
}
}
mlearning_mat_string*mlearning_mat_string_transpose(mlearning_mat_string*matrix,mlearning_mat_string*transposed_matrix)
{
index_t r,c;
char*str;
if(matrix==NULL) return NULL;
if(transposed_matrix==NULL)
{
transposed_matrix=mlearning_mat_string_create_new(matrix->columns,matrix->rows);
if(transposed_matrix==NULL) return NULL;
}
else 
{
if(transposed_matrix->rows!=matrix->columns || transposed_matrix->columns!=matrix->rows) return NULL;
}
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
mlearning_mat_string_get(matrix,r,c,&str);
mlearning_mat_string_set(transposed_matrix,c,r,str);
free(str);
}
}
return transposed_matrix;
}


void mlearning_mat_string_copy(mlearning_mat_string*target,mlearning_mat_string*source,index_t target_row_index,index_t target_column_index,index_t source_from_row_index,index_t source_from_column_index,index_t source_to_row_index,index_t source_to_column_index)
{
index_t target_row;
index_t source_row;
index_t target_column;
index_t source_column;
char*ptr;
if(target==NULL || source==NULL) return;
if(target_row_index<0 || target_row_index>=target->rows) return;
if(target_column_index<0 || target_column_index>=target->columns) return;
if(source_from_row_index<0 || source_from_row_index>=source->rows) return;
if(source_from_column_index<0 || source_from_column_index>=source->columns) return;
if(source_to_row_index<0 || source_to_row_index>=source->rows) return;
if(source_to_column_index<0 || source_to_column_index>=source->columns) return;
if(source_from_row_index>source_to_row_index) return;
if(source_from_column_index>source_to_column_index) return;

target_row=target_row_index;
source_row=source_from_row_index;
while(source_row<=source_to_row_index)
{
target_column=target_column_index;
source_column=source_from_column_index;
while(source_column<=source_to_column_index)
{
if(target_row>=0 && target_row<target->rows && target_column>=0 && target_column<target->columns)
{
if(target->data[target_row][target_column]!=NULL)
{
free(target->data[target_row][target_column]);
target->data[target_row][target_column]=NULL;
}
mlearning_mat_string_get(source,source_row,source_column,&ptr);
if(ptr!=NULL)
{
mlearning_mat_string_set(target,target_row,target_column,ptr);
free(ptr);
}
}
source_column++;
target_column++;
}
source_row++;
target_row++;
}

}
mlearning_mat_string* mlearning_mat_string_shuffle(mlearning_mat_string*matrix,uint8_t shuffle_count,mlearning_mat_string*shuffled_matrix)
{
int u,j;
int r;
index_t end_at_index;
index_t idx;
index_t a,b;
index_t c;
char*tmp_value;
if(matrix==NULL) return NULL;
if(shuffle_count==0) return NULL;
if(shuffled_matrix==NULL)
{
shuffled_matrix=mlearning_mat_string_create_new(matrix->rows,matrix->columns);
if(shuffled_matrix==NULL) return NULL;
}
else 
{
if(shuffled_matrix->rows!=matrix->rows || shuffled_matrix->columns!=matrix->columns) return NULL;
}
mlearning_mat_string_copy(shuffled_matrix,matrix,0,0,0,0,matrix->rows-1,matrix->columns-1);
b=shuffled_matrix->rows-1;
end_at_index=shuffled_matrix->rows-3;
srand(time(NULL));
for(j=1;j<=shuffle_count;j++)
{
for(u=0;u<=end_at_index;u++)
{
a=u+1;
r=rand();
idx=(r%(b-a+1))+a;
//swap values at idx and u 
for(c=0;c<shuffled_matrix->columns;c++)
{
tmp_value=shuffled_matrix->data[u][c];
shuffled_matrix->data[u][c]=shuffled_matrix->data[idx][c];
shuffled_matrix->data[idx][c]=tmp_value;
}
}
}
return shuffled_matrix;
}