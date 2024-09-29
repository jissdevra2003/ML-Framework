#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

typedef struct __mlearning_mat_double
{
double**data;
dimension_t rows;
dimension_t columns;
}mlearning_mat_double;
void mlearning_mat_double_destroy(mlearning_mat_double * matrix)
{
if(matrix==NULL) return;
dimension_t r;
for(r=0;r<matrix->rows;r++)
{
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
}
mlearning_mat_double * mlearning_mat_double_create_new(dimension_t rows,dimension_t columns)
{
mlearning_mat_double*matrix;
index_t r,k;
if(rows<=0 || columns<=0)
{
return NULL;
}
matrix=(mlearning_mat_double *)malloc(sizeof(mlearning_mat_double));
if(matrix==NULL)
{
return NULL;
}
matrix->data=(double **)malloc(sizeof(double *)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}
for(r=0;r<rows;r++)
{
matrix->data[r]=(double*)malloc(sizeof(double)*columns);
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
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}
mlearning_mat_double * mlearning_mat_double_from_csv(const char*csv_file_name,mlearning_mat_double*matrix,mlearning_row_vec_string**header)
{
dimension_t rows,columns;
index_t r,c;
int index;
char m;
double value;
char header_string[1507];
index_t header_index;
index_t header_size;
char double_string[1025];
FILE*file;
if(csv_file_name==NULL || header==NULL) return NULL; //header is also compulsary
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
//the no. of columns in header should be the same as the no. of data columns
if(columns!=header_size)  //if header size is not equal to the columns in the file then no further processing
{
mlearning_row_vec_string_destroy(*header);
fclose(file);
*header=NULL;
return NULL;
}
if(matrix==NULL)
{
matrix=mlearning_mat_double_create_new(rows,columns);
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

rewind(file);  //take the internal pointer to the first byte of file
//skip the first header line and start reading data from 2nd row
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}

index=0;
r=0;
c=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')  //terminate string and fill value
{
double_string[index]='\0';
value=strtod(double_string,NULL);
index=0;
matrix->data[r][c]=value;
c++;
if(c==matrix->columns)
{
r++;
c=0;
}
}
else
{
double_string[index]=m;
index++;
}
if(r==matrix->rows) break;
}
fclose(file);
return matrix;
}

void mlearning_mat_double_set(mlearning_mat_double*matrix,index_t row,index_t column,double value)
{
if(matrix==NULL) return;
if(row<0 || row>=matrix->rows) return;
if(column<0 || column>=matrix->columns) return;
matrix->data[row][column]=value;
}
double mlearning_mat_double_get(mlearning_mat_double*matrix,index_t row,index_t column)
{
double value=0.0;
if(matrix==NULL) return value;
if(row<0 || row>=matrix->rows) return value;
if(column<0 || column>=matrix->columns) return value;
return matrix->data[row][column];
}

void mlearning_mat_double_get_dimensions(mlearning_mat_double*matrix,dimension_t *rows,dimension_t *columns)
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
void mlearning_mat_double_copy(mlearning_mat_double*target_matrix,mlearning_mat_double*source_matrix,index_t target_row_index,index_t target_column_index,index_t source_from_row_index,index_t source_from_column_index,index_t source_to_row_index,index_t source_to_column_index)
{
index_t source_row;
index_t target_row;
index_t source_column;
index_t target_column;
if(target_matrix==NULL || source_matrix==NULL) return;

if(target_row_index<0 || target_row_index>=target_matrix->rows) return;

if(target_column_index<0 || target_column_index>=target_matrix->columns) return;

if(source_from_row_index<0 || source_from_row_index>=source_matrix->rows) return;

if(source_from_column_index<0 || source_from_column_index>=source_matrix->columns) return;

if(source_to_row_index<0 || source_to_row_index>=source_matrix->rows) return;

if(source_to_column_index<0 || source_to_column_index>=source_matrix->columns) return;

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
if(target_row>=0 && target_row<target_matrix->rows && target_column>=0 && target_column<target_matrix->columns)
{
target_matrix->data[target_row][target_column]=source_matrix->data[source_row][source_column];
}
source_column++;
target_column++;
}
source_row++;
target_row++;
}
}
void mlearning_mat_double_fill(mlearning_mat_double*matrix,index_t from_row_index,index_t from_column_index,index_t to_row_index,index_t to_column_index,double value)
{
if(matrix==NULL) return;
index_t r,c;
if(from_row_index<0) from_row_index=0;
if(from_column_index<0) from_column_index=0;
if(from_row_index>=matrix->rows) return;
if(from_column_index>=matrix->columns) return;
if(to_row_index>=matrix->rows) to_row_index=matrix->rows-1;
if(to_column_index>=matrix->columns) to_column_index=matrix->columns-1;
if(from_row_index>to_row_index) return;
if(from_column_index>to_column_index) return;
for(r=from_row_index;r<=to_row_index;r++)
{
for(c=from_column_index;c<=to_column_index;c++)
{
matrix->data[r][c]=value;
}
}
}

mlearning_column_vec_double*mlearning_mat_double_create_column_vec(mlearning_mat_double*matrix,index_t column_index,mlearning_column_vec_double*vector)
{
index_t r;
if(matrix==NULL) return NULL;
if(column_index<0 || column_index>=matrix->columns) return NULL;

if(vector==NULL)
{
vector=mlearning_column_vec_double_create_new(matrix->rows);
if(vector==NULL) return NULL;
}
else 
{
if(mlearning_column_vec_double_get_size(vector)!=matrix->rows) return NULL;
}


for(r=0;r<matrix->rows;r++)
{
mlearning_column_vec_double_set(vector,r,matrix->data[r][column_index]);
}
return vector;
}

mlearning_mat_double* mlearning_mat_double_shuffle(mlearning_mat_double*matrix,uint8_t shuffle_count,mlearning_mat_double*shuffled_matrix)
{
index_t u,idx;
index_t a,b;
index_t end_at_index;
double tmp_value;
index_t c;
uint8_t j;
int r;
if(matrix==NULL) return NULL;
if(shuffle_count==0) return NULL;

if(shuffled_matrix==NULL)
{
shuffled_matrix=mlearning_mat_double_create_new(matrix->rows,matrix->columns);
if(shuffled_matrix==NULL) return NULL;
}
else 
{
if(shuffled_matrix->rows!=matrix->rows || shuffled_matrix->columns!=matrix->columns) return NULL;
}

mlearning_mat_double_copy(shuffled_matrix,matrix,0,0,0,0,matrix->rows-1,matrix->columns-1);
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
//swap data of row index u and idx

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

void mlearning_mat_double_to_csv(mlearning_mat_double*matrix,char*csv_file_name,mlearning_row_vec_string*header)
{
index_t r,c;
dimension_t header_size;
index_t index;
char*ptr;
char seperator;
FILE*file;
if(matrix==NULL || csv_file_name==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
if(header_size!=matrix->columns) return;
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
fprintf(file,"%lf",matrix->data[r][c]);
if(c==matrix->columns-1)
{
seperator='\n';
}
else
{
seperator=',';
}
fputc(seperator,file);
}
}
fclose(file);
}

mlearning_mat_double*mlearning_mat_double_transpose(mlearning_mat_double*matrix,mlearning_mat_double*transposed_matrix)
{
index_t r,c;
if(matrix==NULL) return NULL;

if(transposed_matrix==NULL)
{
transposed_matrix=mlearning_mat_double_create_new(matrix->columns,matrix->rows);
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
transposed_matrix->data[c][r]=matrix->data[r][c];
}
}
return transposed_matrix;
}

double mlearning_mat_double_get_minimum(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double minimum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(start_column_index<0) start_column_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0; 
minimum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]<minimum)
{
minimum=matrix->data[r][c];
}
}
}
return minimum;
}
double mlearning_mat_double_get_maximum(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double maximum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0) start_row_index=0;
if(start_column_index<0) start_column_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index) return 0.0;
if(start_column_index>end_column_index) return 0.0;
maximum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]>maximum)
{
maximum=matrix->data[r][c];
}
}
}
return maximum;
}


double mlearning_mat_double_get_mean(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double mean;
double sum;
dimension_t e_count;
index_t r,c;
if(start_row_index<0) start_row_index=0;
if(start_column_index<0) start_column_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(end_column_index>=matrix->columns) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index || start_column_index>end_column_index) return 0.0;
sum=0.0;
e_count=0;
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
sum=matrix->data[r][c]+sum;
e_count++;
}
}
mean=sum/e_count;
return mean;
}

double mlearning_mat_double_get_standard_deviation(mlearning_mat_double*matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double standard_deviation;
double mean;
double square;
double sum;
double difference;
dimension_t e_count;
index_t r,c;
if(start_row_index<0) start_row_index=0;
if(start_column_index<0) start_column_index=0;
if(end_row_index>=matrix->rows) end_row_index=matrix->rows-1;
if(end_column_index>=matrix->columns-1) end_column_index=matrix->columns-1;
if(start_row_index>end_row_index || start_column_index>end_column_index) return 0.0;
mean=mlearning_mat_double_get_mean(matrix,start_row_index,start_column_index,end_row_index,end_column_index);
sum=0.0;
difference=0.0;
e_count=0;
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
difference=matrix->data[r][c]-mean;
square=difference*difference;
sum=sum+square;
e_count++;
}
}
mean=sum/e_count;
standard_deviation=sqrt(mean);
return standard_deviation;
}

void mlearning_mat_double_load_training_testing_data(char*csv_file_name,mlearning_mat_double**training_data,mlearning_mat_double**testing_data,uint8_t test_data_percentage)
{
mlearning_mat_double*matrix;
mlearning_mat_double*minor_matrix;
mlearning_mat_double*major_matrix;
//gfgf
mlearning_row_vec_string*header;
mlearning_mat_double*shuffled_matrix;
dimension_t shuffled_matrix_rows,shuffled_matrix_columns;
dimension_t minor_rows;
dimension_t major_rows;
index_t i,j;
if(csv_file_name==NULL)
{
*training_data=NULL;
*testing_data=NULL;
return;
}
if(training_data==NULL || testing_data==NULL)
{
if(training_data!=NULL) *training_data=NULL;
if(testing_data!=NULL) *testing_data=NULL;
return;
}
if(test_data_percentage<=0 || test_data_percentage>=100) 
{
*training_data=NULL;
*testing_data=NULL;
return;
}
matrix=mlearning_mat_double_from_csv(csv_file_name,NULL,&header);
if(matrix==NULL)
{
*training_data=NULL;
*testing_data=NULL;
return;
}

shuffled_matrix=mlearning_mat_double_shuffle(matrix,7,NULL);
if(shuffled_matrix==NULL)
{
*training_data=NULL;
*testing_data=NULL;
mlearning_mat_double_destroy(matrix);
mlearning_row_vec_string_destroy(header);
return;
}

mlearning_mat_double_get_dimensions(shuffled_matrix,&shuffled_matrix_rows,&shuffled_matrix_columns);
minor_rows=(dimension_t)(test_data_percentage*shuffled_matrix_rows)/100;
major_rows=shuffled_matrix_rows-minor_rows;

major_matrix=(mlearning_mat_double*)malloc(sizeof(mlearning_mat_double));
if(major_matrix==NULL)
{
*training_data=NULL;
*testing_data=NULL;
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_row_vec_string_destroy(header);
return;
}
major_matrix->rows=major_rows;
major_matrix->columns=shuffled_matrix_columns;

major_matrix->data=(double**)malloc(sizeof(double*)*major_rows);
if(major_matrix->data==NULL)
{
*training_data=NULL;
*testing_data=NULL;
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_row_vec_string_destroy(header);
free(major_matrix);
return;
}
for(i=0,j=0;i<major_rows;i++,j++)
{
major_matrix->data[i]=shuffled_matrix->data[j];
}

minor_matrix=(mlearning_mat_double*)malloc(sizeof(mlearning_mat_double));
if(minor_matrix==NULL)
{
*training_data=NULL;
*testing_data=NULL;
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_row_vec_string_destroy(header);
free(major_matrix->data);
free(major_matrix);
return;
}

minor_matrix->rows=minor_rows;
minor_matrix->columns=shuffled_matrix_columns;
minor_matrix->data=(double**)malloc(sizeof(double*)*minor_rows);
if(minor_matrix->data==NULL)
{
*training_data=NULL;
*testing_data=NULL;
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_row_vec_string_destroy(header);
free(major_matrix->data);
free(major_matrix);
free(minor_matrix);
return;
}
for(i=0;i<minor_rows;i++,j++)
{
minor_matrix->data[i]=shuffled_matrix->data[j];
}
*training_data=major_matrix;
*testing_data=minor_matrix;
mlearning_mat_double_destroy(matrix);
free(shuffled_matrix->data);
free(shuffled_matrix);
mlearning_row_vec_string_destroy(header);

}

