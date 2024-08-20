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

mlearning_column_vec_double*mlearning_column_vec_double_create_new_filled(dimension_t size,double value)
{
index_t r;
if(size<=0) return NULL;
mlearning_column_vec_double*vector;
vector=mlearning_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(r=0;r<vector->size;r++)
{
vector->data[r]=value;
}
return vector;
}
mlearning_row_vec_double*mlearning_column_vec_double_transpose(mlearning_column_vec_double*vector)
{
if(vector==NULL) return NULL;
index_t r;
mlearning_row_vec_double*transposed_vector;
transposed_vector=mlearning_row_vec_double_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
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

void mlearning_column_vec_double_to_csv(mlearning_column_vec_double*vector,char*csv_file)
{
FILE*file;
index_t i;
if(vector==NULL || csv_file==NULL) return;
file=fopen(csv_file,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
mlearning_column_vec_double * mlearning_column_vec_double_from_csv(char*csv_file)
{
mlearning_column_vec_double*vector;
index_t j;
int index;
char m;
dimension_t size;
double value;
char double_string[1025];
char*end;
FILE*file;
file=fopen(csv_file,"r");
if(file==NULL) return NULL;
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',') size++;
}
size++;
vector=mlearning_column_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
return NULL;
}

rewind(file);
j=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
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

mlearning_row_vec_double*mlearning_row_vec_double_create_new_filled(dimension_t size,double value)
{
index_t r;
if(size<=0) return NULL;
mlearning_row_vec_double*vector;
vector=mlearning_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(r=0;r<vector->size;r++)
{
vector->data[r]=value;
}
return vector;
}
mlearning_column_vec_double*mlearning_row_vec_double_transpose(mlearning_row_vec_double*vector)
{
if(vector==NULL) return NULL;
index_t r;
mlearning_column_vec_double*transposed_vector;
transposed_vector=mlearning_column_vec_double_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
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

void mlearning_row_vec_double_to_csv(mlearning_row_vec_double*vector,char*csv_file)
{
FILE*file;
index_t i;
if(vector==NULL || csv_file==NULL) return;
file=fopen(csv_file,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}


mlearning_row_vec_double * mlearning_row_vec_double_from_csv(char*csv_file)
{
mlearning_row_vec_double*vector;
index_t j;
int index;
char m;
dimension_t size;
double value;
char double_string[1025];
char*end;
FILE*file;
file=fopen(csv_file,"r");
if(file==NULL) return NULL;
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',') size++;
}
size++;
vector=mlearning_row_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
return NULL;
}

rewind(file);
j=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
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
