#include<mlearning_matrix.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

mlearning_mat_string * mlearning_mat_string_from_csv(const char*csv_file_name)
{
mlearning_mat_string*matrix;
index_t r,c;
dimension_t rows,columns;
char m;
int index;
char string[7021];
FILE*file;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
rows=0;
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(rows==0)
{
if(m==',') columns++;
}
if(m=='\n') rows++;
}
columns++;

matrix=mlearning_mat_string_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
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

void mlearning_mat_string_to_csv(mlearning_mat_string*matrix,const char*csv_file_name)
{
FILE*file;
index_t r,c;
if(matrix==NULL) return;
if(csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
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