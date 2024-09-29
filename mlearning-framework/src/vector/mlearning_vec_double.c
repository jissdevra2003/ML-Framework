#include<stdio.h>
#include<stdlib.h>
#include<mlearning_vector.h>
typedef struct __mlearning_column_vec_double
{
double* data;
dimension_t size;
}mlearning_column_vec_double;
typedef struct __mlearning_row_vec_double
{
double*data;
dimension_t size;
}mlearning_row_vec_double;


//column functions
mlearning_column_vec_double* mlearning_column_vec_double_create_new(dimension_t size)
{
if(size<=0) return NULL;
mlearning_column_vec_double*vector;
vector=(mlearning_column_vec_double*)malloc(sizeof(mlearning_column_vec_double));
if(vector==NULL) return NULL;
vector->data=(double*)malloc(sizeof(double)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}
void mlearning_column_vec_double_destroy(mlearning_column_vec_double*vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
}
double mlearning_column_vec_double_get(mlearning_column_vec_double*vector,index_t index)
{
if(vector==NULL) return 0.0;
if(index<0 || index>=vector->size) return 0.0;
return vector->data[index];
}

void mlearning_column_vec_double_set(mlearning_column_vec_double*vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}

mlearning_column_vec_double*mlearning_column_vec_double_create_new_filled(dimension_t size,double value,mlearning_column_vec_double*vector)
{
index_t r;
if(size<=0) return NULL;

if(vector==NULL)
{
vector=mlearning_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
}
else 
{
if(vector->size!=size) return NULL;
}


for(r=0;r<vector->size;r++)
{
vector->data[r]=value;
}
return vector;
}
mlearning_row_vec_double*mlearning_column_vec_double_transpose(mlearning_column_vec_double*vector,mlearning_row_vec_double*transposed_vector)
{
if(vector==NULL) return NULL;
index_t r;

if(transposed_vector==NULL)
{
transposed_vector=mlearning_row_vec_double_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
}
else 
{
if(transposed_vector->size!=vector->size) return NULL;
}

for(r=0;r<vector->size;r++)
{
transposed_vector->data[r]=vector->data[r];
}
return transposed_vector;
}
dimension_t mlearning_column_vec_double_get_size(mlearning_column_vec_double*vector)
{
if(vector==NULL) return 0;
return vector->size;
}

double mlearning_column_vec_double_get_mean(mlearning_column_vec_double*vector)
{
double mean,sum;
index_t i;
if(vector==NULL) return 0.0;
sum=0.0;
for(i=0;i<vector->size;i++)
{
sum+=vector->data[i];
}
mean=sum/(double)vector->size;
return mean;

}

void mlearning_column_vec_double_to_csv(mlearning_column_vec_double*vector,char*csv_file,mlearning_row_vec_string*header)
{
dimension_t header_size;
index_t index;
char*ptr;
FILE*file;
index_t i;
if(vector==NULL || csv_file==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
if(header_size!=1) return;
file=fopen(csv_file,"w");
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




for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
mlearning_column_vec_double * mlearning_column_vec_double_from_csv(char*csv_file,mlearning_column_vec_double*vector,mlearning_row_vec_string**header)
{
index_t j;
int index;
dimension_t header_size;
index_t header_index;
char header_string[1507];
char m;
dimension_t size; 
double value;
char double_string[1025];
char*end;
FILE*file;
if(csv_file==NULL || header==NULL) return NULL;
file=fopen(csv_file,"r");
if(file==NULL) return NULL;

//logic to read the header line starts
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
if(header_size!=1)
{
fclose(file);
*header=NULL;
return NULL;
}
*header=mlearning_row_vec_string_create_new(header_size);
if(*header==NULL)
{
fclose(file);
return NULL;
}
header_index=0;
index=0;
rewind(file);
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


size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') size++;
}
size++;

if(vector==NULL)
{
vector=mlearning_column_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else 
{
if(vector->size!=size) 
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}


rewind(file);
//skip the first header line
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}

j=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
double_string[index]='\0';
end=NULL;
value=strtod(double_string,&end);
mlearning_column_vec_double_set(vector,j,value);
j++; 
index=0;
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return vector;
}


//row functions
mlearning_row_vec_double*mlearning_row_vec_double_create_new(dimension_t size)
{
if(size<=0) return NULL;
mlearning_row_vec_double*vector;
vector=(mlearning_row_vec_double*)malloc(sizeof(mlearning_row_vec_double));
if(vector==NULL) return NULL;
vector->data=(double*)malloc(sizeof(double)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}
void mlearning_row_vec_double_destroy(mlearning_row_vec_double*vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
}
double mlearning_row_vec_double_get(mlearning_row_vec_double*vector,index_t index)
{
if(vector==NULL) return 0.0;
if(index<0 || index>=vector->size) return 0.0;
return vector->data[index];
}

void mlearning_row_vec_double_set(mlearning_row_vec_double*vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}

mlearning_row_vec_double*mlearning_row_vec_double_create_new_filled(dimension_t size,double value,mlearning_row_vec_double*vector)
{
index_t r;
if(size<=0) return NULL;

if(vector==NULL)
{
vector=mlearning_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
}
else 
{
if(vector->size!=size) return NULL;
}

for(r=0;r<vector->size;r++)
{
vector->data[r]=value;
}
return vector;
}
mlearning_column_vec_double*mlearning_row_vec_double_transpose(mlearning_row_vec_double*vector,mlearning_column_vec_double*transposed_vector)
{
if(vector==NULL) return NULL;
index_t r;

if(transposed_vector==NULL)
{
transposed_vector=mlearning_column_vec_double_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
}
else 
{
if(transposed_vector->size!=vector->size) return NULL;
}

for(r=0;r<vector->size;r++)
{
transposed_vector->data[r]=vector->data[r];
}
return transposed_vector;
}
dimension_t mlearning_row_vec_double_get_size(mlearning_row_vec_double*vector)
{
if(vector==NULL) return 0;
return vector->size;
}

double mlearning_row_vec_double_get_mean(mlearning_row_vec_double*vector)
{
double mean,sum;
index_t i;
if(vector==NULL) return 0.0;
sum=0.0;
for(i=0;i<vector->size;i++)
{
sum+=vector->data[i];
}
mean=sum/(double)vector->size;
return mean;
}

void mlearning_row_vec_double_to_csv(mlearning_row_vec_double*vector,char*csv_file,mlearning_row_vec_string*header)
{
dimension_t header_size;
char*ptr;
index_t index;
FILE*file;
index_t i;
if(vector==NULL || csv_file==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
if(header_size!=vector->size) return;
file=fopen(csv_file,"w");
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



for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}


mlearning_row_vec_double * mlearning_row_vec_double_from_csv(char*csv_file,mlearning_row_vec_double*vector,mlearning_row_vec_string**header)
{
index_t j;
int index;
dimension_t header_size;
index_t header_index;
char header_string[1507];
char m;
dimension_t size;
double value;
char double_string[1025];
char*end;
FILE*file;
if(csv_file==NULL || header==NULL) return NULL;
file=fopen(csv_file,"r");
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




size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',') size++;
}
size++; //data rows size should match the header size
if(header_size!=size)
{
mlearning_row_vec_string_destroy(*header);
fclose(file);
*header=NULL;
return NULL;
}

if(vector==NULL)
{
vector=mlearning_row_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}
else 
{
if(vector->size!=size) 
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
}


rewind(file);
//skip the first header line 
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}
j=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m==',' || m=='\n')
{
double_string[index]='\0';
end=NULL;
value=strtod(double_string,&end);
mlearning_row_vec_double_set(vector,j,value);
j++; 
index=0;
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return vector;
}
