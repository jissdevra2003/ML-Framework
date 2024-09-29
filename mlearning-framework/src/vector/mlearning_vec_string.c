#include<mlearning_vector.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
typedef struct __mlearning_column_vec_string
{
char**data;
dimension_t size;
}mlearning_column_vec_string;
typedef struct __mlearning_row_vec_string
{
char**data;
dimension_t size;
}mlearning_row_vec_string;


//row functions
void mlearning_row_vec_string_destroy(mlearning_row_vec_string * vector)
{
index_t i;
if(vector==NULL) return;
for(i=0;i<vector->size;i++)
{
if(vector->data[i]!=NULL) free(vector->data[i]);
}
free(vector->data);
free(vector);
return;
}
mlearning_row_vec_string * mlearning_row_vec_string_create_new(dimension_t size)
{
mlearning_row_vec_string*vector;
index_t i;
if(size<=0) return NULL;
vector=(mlearning_row_vec_string*)malloc(sizeof(mlearning_row_vec_string));
if(vector==NULL) return NULL;
vector->data=(char**)malloc(sizeof(char*)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
for(i=0;i<size;i++) vector->data[i]=NULL;
vector->size=size;
return vector;
}
<<<<<<< HEAD
mlearning_row_vec_string * mlearning_row_vec_string_from_csv(const char* csv_file_name,mlearning_row_vec_string*vector,mlearning_row_vec_string**header)
{
index_t i;
int index;
dimension_t header_size;
index_t header_index;
char header_string[1507];
char string[5021];
char m;
dimension_t size;
FILE*file;
if(csv_file_name==NULL || header==NULL) return NULL;
=======
mlearning_row_vec_string * mlearning_row_vec_string_from_csv(const char* csv_file_name)
{
index_t i;
int index;
char string[5021];
char m;
dimension_t size;
mlearning_row_vec_string*vector;
FILE*file;
if(csv_file_name==NULL) return NULL;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
file=fopen(csv_file_name,"r");
if(file==NULL)
{
return NULL;
}
<<<<<<< HEAD

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




=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
<<<<<<< HEAD
if(m=='\r') continue;
if(m==',') size++;
}
size++;
if(size!=header_size)
{
fclose(file);
mlearning_row_vec_string_destroy(*header);
*header=NULL;
return NULL;
}
if(vector==NULL)
{
=======
if(m==',') size++;
}
size++;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
vector=mlearning_row_vec_string_create_new(size);
if(vector==NULL)
{
fclose(file);
<<<<<<< HEAD
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

rewind(file); // take the internal pointer to the first byte of file
//skip the first header line 
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m=='\r') continue;
if(m=='\n') break;
}
index=0;
i=0;
//populating the data into vector
=======
return NULL;
}
index=0;
i=0;
rewind(file);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
while(1)
{
m=fgetc(file);
if(feof(file)) break;
<<<<<<< HEAD
if(m=='\r') continue;
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(m==',' || m=='\n')
{
string[index]='\0';
index=0;
mlearning_row_vec_string_set(vector,i,string);
i++;
}
else
{
string[index]=m;
index++;
}
}
fclose(file);
return vector;
}
<<<<<<< HEAD
void mlearning_row_vec_string_to_csv(mlearning_row_vec_string*vector,const char*csv_file_name,mlearning_row_vec_string*header)
{
char*ptr;
dimension_t header_size;
index_t index;
FILE*file;
index_t i; 
if(vector==NULL) return;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
if(header_size!=vector->size) return;
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



=======
void mlearning_row_vec_string_to_csv(mlearning_row_vec_string*vector,const char*csv_file_name)
{
FILE*file;
index_t i; 
if(vector==NULL) return;
if(csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
for(i=0;i<vector->size;i++)
{
if(vector->data[i]!=NULL) fputs(vector->data[i],file); 
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
void mlearning_row_vec_string_set(mlearning_row_vec_string*vector,index_t index,char*string)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
if(string==NULL) return;
if(vector->data[index]!=NULL) free(vector->data[index]);
vector->data[index]=(char*)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[index]!=NULL) 
{
strcpy(vector->data[index],string);
}
}
void mlearning_row_vec_string_get(mlearning_row_vec_string*vector,index_t index,char**string)
{
if(string==NULL) return;
if(vector==NULL)
{
*string=NULL;
 return;
}
if(index<0 || index>=vector->size)
{
*string=NULL;
 return;
}
if(vector->data[index]==NULL)
{
*string=NULL;
return;
}
*string=(char*)malloc(sizeof(char)*(strlen(vector->data[index])+1));
if(*string!=NULL)
{
strcpy(*string,vector->data[index]);
}
}
dimension_t mlearning_row_vec_string_get_size(mlearning_row_vec_string*vector)
{
if(vector==NULL) return 0;
return vector->size;
}
<<<<<<< HEAD
mlearning_column_vec_string*mlearning_row_vec_string_transpose(mlearning_row_vec_string*vector,mlearning_column_vec_string*transposed_vector)
{
index_t i;
char*str;
if(vector==NULL) return NULL;

if(transposed_vector==NULL)
{
transposed_vector=mlearning_column_vec_string_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
}
else 
{
if(transposed_vector->size!=vector->size) return NULL;
}


=======
mlearning_column_vec_string*mlearning_row_vec_string_transpose(mlearning_row_vec_string*vector)
{
index_t i;
char*str;
mlearning_column_vec_string*transposed_vector;
if(vector==NULL) return NULL;
transposed_vector=mlearning_column_vec_string_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
for(i=0;i<vector->size;i++)
{
mlearning_row_vec_string_get(vector,i,&str);
mlearning_column_vec_string_set(transposed_vector,i,str);
free(str);
}
return transposed_vector;
}


//column functions
void mlearning_column_vec_string_destroy(mlearning_column_vec_string * vector)
{
index_t i;
if(vector==NULL) return;
for(i=0;i<vector->size;i++)
{
free(vector->data[i]);
}
free(vector->data);
free(vector);
return;
}
mlearning_column_vec_string * mlearning_column_vec_string_create_new(dimension_t size)
{
mlearning_column_vec_string*vector;
index_t i;
if(size<=0) return NULL;
vector=(mlearning_column_vec_string*)malloc(sizeof(mlearning_column_vec_string));
if(vector==NULL) return NULL;
vector->data=(char**)malloc(sizeof(char*)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
for(i=0;i<size;i++) vector->data[i]=NULL;
vector->size=size;
return vector;
}
<<<<<<< HEAD
mlearning_column_vec_string * mlearning_column_vec_string_from_csv(const char* csv_file_name,mlearning_column_vec_string*vector,mlearning_row_vec_string**header)
{
index_t i;
int index;
dimension_t header_size;
index_t header_index;
char header_string[1507];
char string[5021];
char m;
dimension_t size;
FILE*file;
if(csv_file_name==NULL || header==NULL) return NULL;
=======
mlearning_column_vec_string * mlearning_column_vec_string_from_csv(const char* csv_file_name)
{
index_t i;
int index;
char string[5021];
char m;
dimension_t size;
mlearning_column_vec_string*vector;
FILE*file;
if(csv_file_name==NULL) return NULL;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
file=fopen(csv_file_name,"r");
if(file==NULL)
{
return NULL;
}
<<<<<<< HEAD

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
if(header_size!=1)  //column vector contains only 1 column
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


=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
<<<<<<< HEAD
if(m=='\r') continue;
if(m==',') size++;
}
size++;

if(vector==NULL)
{
=======
if(m==',') size++;
}
size++;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
vector=mlearning_column_vec_string_create_new(size);
if(vector==NULL)
{
fclose(file);
<<<<<<< HEAD
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

index=0;
i=0;
=======
return NULL;
}
index=0;
i=0;
rewind(file);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
while(1)
{
m=fgetc(file);
if(feof(file)) break;
<<<<<<< HEAD
if(m=='\r') continue;
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(m==',' || m=='\n')
{
string[index]='\0';
index=0;
mlearning_column_vec_string_set(vector,i,string);
i++;
}
else
{
string[index]=m;
index++;
}
}
fclose(file);
return vector;
}
<<<<<<< HEAD
void mlearning_column_vec_string_to_csv(mlearning_column_vec_string*vector,const char*csv_file_name,mlearning_row_vec_string*header)
{
dimension_t header_size;
index_t index;
char*ptr;
FILE*file;
index_t i;
if(vector==NULL) return;
if(csv_file_name==NULL || header==NULL) return;
header_size=mlearning_row_vec_string_get_size(header);
//column vector header will also contain 1 column
if(header_size!=1) return; 
file=fopen(csv_file_name,"w");
if(file==NULL) return;

//code to write header in file on first line
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



=======
void mlearning_column_vec_string_to_csv(mlearning_column_vec_string*vector,const char*csv_file_name)
{
FILE*file;
index_t i;
if(vector==NULL) return;
if(csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
for(i=0;i<vector->size;i++)
{
if(vector->data[i]!=NULL) fputs(vector->data[i],file);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}
void mlearning_column_vec_string_set(mlearning_column_vec_string*vector,index_t index,char*string)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
if(string==NULL) return;
if(vector->data[index]!=NULL) free(vector->data[index]);
vector->data[index]=(char*)malloc(sizeof(char)*(strlen(string)+1));
if(vector->data[index]!=NULL) 
{
strcpy(vector->data[index],string);
}
}
void mlearning_column_vec_string_get(mlearning_column_vec_string*vector,index_t index,char**string)
{
if(string==NULL) return;
if(vector==NULL)
{
*string=NULL;
 return;
}
if(index<0 || index>=vector->size)
{
*string=NULL;
 return;
}
if(vector->data[index]==NULL)
{
*string=NULL;
return;
}
*string=(char*)malloc(sizeof(char)*(strlen(vector->data[index])+1));
if(*string!=NULL)
{
strcpy(*string,vector->data[index]);
}
}
dimension_t mlearning_column_vec_string_get_size(mlearning_column_vec_string*vector)
{
if(vector==NULL) return 0;
return vector->size;
}
<<<<<<< HEAD
mlearning_row_vec_string*mlearning_column_vec_string_transpose(mlearning_column_vec_string*vector,mlearning_row_vec_string*transposed_vector)
{
index_t i;
char*str;
if(vector==NULL) return NULL;

if(transposed_vector==NULL)
{
transposed_vector=mlearning_row_vec_string_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
}
else 
{
if(transposed_vector->size!=vector->size) return NULL;
}


=======
mlearning_row_vec_string*mlearning_column_vec_string_transpose(mlearning_column_vec_string*vector)
{
index_t i;
char*str;
mlearning_row_vec_string*transposed_vector;
if(vector==NULL) return NULL;
transposed_vector=mlearning_row_vec_string_create_new(vector->size);
if(transposed_vector==NULL) return NULL;
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
for(i=0;i<vector->size;i++)
{
mlearning_column_vec_string_get(vector,i,&str);
mlearning_row_vec_string_set(transposed_vector,i,str);
free(str);
}
return transposed_vector;
}
