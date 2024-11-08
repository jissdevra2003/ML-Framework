#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<stdlib.h>
#include<stdio.h>
//#include<pthread.h>
#include<windows.h>

//global variable
uint64_t NUMBER_OF_ITERATIONS=-1;
char* DATASET_FILE_NAME=NULL;
double LEARNING_RATE=1.0;
uint32_t HISTORY_SIZE=0;
char*HISTORY_FILE_NAME=NULL;
char*PARAMETERS_FILE_NAME=NULL;
char*GRAPH_FILE_NAME=NULL;
uint8_t STOP_FLAG=0;


void train_it()
{
FILE*graph_file;
char header_title[20];
mlearning_mat_double*history;
mlearning_row_vec_string*history_header=NULL;
dimension_t history_rows,history_columns;
index_t history_index;
index_t i,j;
uint32_t error_flag;
double iteration_number;
double value;

uint64_t k;
int t;
mlearning_mat_double*dataset;
mlearning_row_vec_string*dataset_header;
dimension_t dataset_rows;
dimension_t dataset_columns;

mlearning_mat_double*I;
dimension_t I_rows;
dimension_t I_columns;
dimension_t P_vector_size;
dimension_t E_vector_size;

mlearning_column_vec_double*A;
mlearning_column_vec_double*m;
mlearning_row_vec_string*model_header;  //parameters file header
mlearning_column_vec_double*P;
mlearning_column_vec_double*E;
mlearning_row_vec_double*ET;
mlearning_column_vec_double*ETE;
mlearning_mat_double*IT;
mlearning_column_vec_double*ITE;
mlearning_column_vec_double*TMP;
mlearning_column_vec_double*UM;
double sum_of_squared_error_values=0.0;
double final_error_value=0.0;

dataset=mlearning_mat_double_from_csv(DATASET_FILE_NAME,NULL,&dataset_header);
if(dataset==NULL)
{
printf("Unable to load the dataset from %s\n",DATASET_FILE_NAME);
return;
}
mlearning_mat_double_get_dimensions(dataset,&dataset_rows,&dataset_columns);


I_rows=dataset_rows;
I_columns=dataset_columns-1+1;


I=mlearning_mat_double_create_new(I_rows,I_columns);
if(I==NULL)
{
printf("Unable to create matrix I\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
return;
}
history_rows=HISTORY_SIZE;
// 1 for iteration number at 0 column  index , 2 for error value at 1 column index remaining for storing m vector values.
history_columns=I_columns+2;  

history=mlearning_mat_double_create_new(history_rows,history_columns);
if(history==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_row_vec_string_destroy(dataset_header);
return;
}

history_header=mlearning_row_vec_string_create_new(history_columns);
if(history_header==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(history);
return;
}
model_header=mlearning_row_vec_string_create_new(I_columns);
if(model_header==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(history);
mlearning_row_vec_string_destroy(history_header);
return;
}
mlearning_row_vec_string_set(history_header,0,"iteration");
mlearning_row_vec_string_set(history_header,1,"error_value");
t=2;
while(t<history_columns)
{
sprintf(header_title,"theta(%d)",t-2);
mlearning_row_vec_string_set(history_header,t,header_title);
mlearning_row_vec_string_set(model_header,t-2,header_title);
t++;
}


mlearning_mat_double_fill(history,0,0,history_rows-1,history_columns-1,0.0);

mlearning_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,dataset_columns-2);

mlearning_mat_double_fill(I,0,0,dataset_rows-1,0,1.0);  //input matrix m 1 fill krna hh



IT=mlearning_mat_double_transpose(I,NULL);
if(IT==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
return;
}

A=mlearning_mat_double_create_column_vec(dataset,dataset_columns-1,NULL);
if(A==NULL)
{
printf("Unable to create column vector A\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
return;
}


m=mlearning_column_vec_double_create_new_filled(I_columns,0.0,NULL);  // 'm' column vector
if(m==NULL)
{
printf("Unable to create column vector m\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
return;
}


P=mlearning_column_vec_double_create_new(I_rows);
if(P==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
return;
}
P_vector_size=mlearning_column_vec_double_get_size(P);

E=mlearning_column_vec_double_create_new(P_vector_size);
if(E==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
return;
}
E_vector_size=mlearning_column_vec_double_get_size(E);

ET=mlearning_row_vec_double_create_new(E_vector_size);
if(ET==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
return;
}

ETE=mlearning_column_vec_double_create_new(1);
if(ETE==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
return;
}

ITE=mlearning_column_vec_double_create_new(I_columns);
if(ITE==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
return;

}

TMP=mlearning_column_vec_double_create_new(I_columns);
if(TMP==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
return;
}

UM=mlearning_column_vec_double_create_new(I_columns);
if(UM==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_column_vec_double_destroy(TMP);
return;
}


graph_file=fopen(GRAPH_FILE_NAME,"w");

//Operations start
history_index=0;
error_flag=0;
k=1;
while(STOP_FLAG==0)
{
if(k==(NUMBER_OF_ITERATIONS+1)) break;
P=mlearning_multiply_double_matrix_with_column_vector(I,m,P);
if(P==NULL)
{
printf("Unable to create column vector P\n");
error_flag=1;
break;
}

E=mlearning_subtract_double_column_vector(P,A,E);
if(E==NULL)
{
printf("Unable to create column vector E\n");
error_flag=1;
break;
}

ET=mlearning_column_vec_double_transpose(E,ET);
if(ET==NULL)
{
printf("Unable to create row vector ET\n");
error_flag=1;
break;
}

ETE=mlearning_multiply_double_row_vector_with_column_vector(ET,E,ETE);
if(ETE==NULL)
{
printf("Unable to create column vector ETE\n");
error_flag=1;
break;
}

sum_of_squared_error_values=mlearning_column_vec_double_get(ETE,0);

final_error_value=sum_of_squared_error_values/(2*I_rows);   //we divided by 1/2n in differentiation formula

//printf("Sum of squared error values :%-41.15lf\n",sum_of_squared_error_values);
printf("Iteration number %" PRIu64 ",Error value :  %41.15lf\n",k,final_error_value);

fprintf(graph_file,"%" PRIu64 ",%lf\n",k,final_error_value);


iteration_number=(double)k;
if(history_index==HISTORY_SIZE)
{
for(i=1;i<HISTORY_SIZE;i++)
{
for(j=0;j<history_columns;j++)
{
value=mlearning_mat_double_get(history,i,j);
mlearning_mat_double_set(history,i-1,j,value);
}
}
history_index--;
}
mlearning_mat_double_set(history,history_index,0,iteration_number);
mlearning_mat_double_set(history,history_index,1,final_error_value);
j=mlearning_column_vec_double_get_size(m);
for(i=0;i<j;i++)
{
value=mlearning_column_vec_double_get(m,i);
mlearning_mat_double_set(history,history_index,2+i,value);
}
history_index++;



//logic to update m & c values technically our m column vector.
//ITE=E^i x x^i
ITE=mlearning_multiply_double_matrix_with_column_vector(IT,E,ITE);   
if(ITE==NULL)
{
printf("Low memory\n");
error_flag=1;
break;
}
//TMP=(1/n)*ITE
TMP=mlearning_multiply_double_scalar_with_column_vector((LEARNING_RATE*(1.0/I_rows)),ITE,TMP);  
if(TMP==NULL)
{
printf("Low memory\n");
error_flag=1;
break;
}
// m^i=m^i - 1/n(E^i x x^i) where i=0,1,2,3...n (i is no. of rows)
UM=mlearning_subtract_double_column_vector(m,TMP,UM); 
if(UM==NULL)
{
printf("Low memory\n");
error_flag=1;
break;
}
for(t=0;t<I_columns;t++)
{
mlearning_column_vec_double_set(m,t,mlearning_column_vec_double_get(UM,t));
}

k++;
}

fclose(graph_file);
if(error_flag==1)
{
//release resources
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_column_vec_double_destroy(TMP);
mlearning_column_vec_double_destroy(UM);
return;
}
//code to store the contents of (m vector) to csv file
mlearning_mat_double_to_csv(history,HISTORY_FILE_NAME,history_header);
mlearning_column_vec_double_to_csv(m,PARAMETERS_FILE_NAME,model_header);

//release resources
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(model_header);
mlearning_row_vec_string_destroy(history_header);
mlearning_mat_double_destroy(I);
mlearning_mat_double_destroy(history);
mlearning_mat_double_destroy(IT);
mlearning_column_vec_double_destroy(A);
mlearning_column_vec_double_destroy(m);
mlearning_column_vec_double_destroy(P);
mlearning_column_vec_double_destroy(E);
mlearning_row_vec_double_destroy(ET);
mlearning_column_vec_double_destroy(ETE);
mlearning_column_vec_double_destroy(ITE);
mlearning_column_vec_double_destroy(TMP);
mlearning_column_vec_double_destroy(UM);


}


// void * thread_function(void*ptr)
// {
// train_it();
// return NULL;
// }
DWORD WINAPI thread_function(LPVOID lptr)
{
train_it();
return 0;
}

int main(int argc,char*argv[])
{
char*ptr;
char m;
//pthread_t thread_id;
DWORD thread_id;
//int result;
HANDLE h_thread;
if(argc!=7 && argc!=8)
{
printf("Usage train_it_refactored.exe _ dataset_file_name _ learning_rate _ history_size _ history_file_name _ parameters_file_name _ graph_file_name _ number_of_iterations(optional)\n");
return 0;
}

DATASET_FILE_NAME=argv[1];
ptr=NULL;
LEARNING_RATE=strtod(argv[2],&ptr);
ptr=NULL;
HISTORY_SIZE=(strtoull(argv[3],&ptr,10));
if(HISTORY_SIZE<5)
{
printf("History size should be greater than 5\n");
return 0;
}
HISTORY_FILE_NAME=argv[4];
PARAMETERS_FILE_NAME=argv[5];
GRAPH_FILE_NAME=argv[6];
if(argc==8)
{
ptr=NULL;
NUMBER_OF_ITERATIONS=strtoull(argv[7],&ptr,10);  //ull(unsigned long long)
}

h_thread=CreateThread(NULL,0,thread_function,NULL,0,&thread_id);
//result=pthread_create(&thread_id,NULL,thread_function,NULL);
//if(result!=0)
// {
// printf("Unable to create thread\n");
// return 0;
// }
if(h_thread==NULL)
{
printf("Unable to create thread\n");
return 0; 
}

while(1)
{
m=getchar();
if(m=='\n')
{
STOP_FLAG=1;
break;
}
}
//pthread_join(thread_id,NULL);
WaitForSingleObject(h_thread,INFINITE);
CloseHandle(h_thread);
return 0;
}




