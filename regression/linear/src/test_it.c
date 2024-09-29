#include<mlearning_matrix.h>
#include<mlearning_vector.h>
#include<mlearning_operations.h>
#include<stdio.h>
#include<stdlib.h>


char*DATASET_FILE_NAME=NULL;
char*RESULTS_FILE_NAME=NULL;
char*PARAMETERS_FILE_NAME=NULL;

void test_it()
{
mlearning_mat_double*dataset;
<<<<<<< HEAD
mlearning_row_vec_string*dataset_header;
=======
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
dimension_t dataset_rows,dataset_columns;
index_t r,c;
mlearning_mat_double*I;
dimension_t I_rows,I_columns;
FILE*results_file;

mlearning_column_vec_double*m;
<<<<<<< HEAD
mlearning_row_vec_string*model_header;
mlearning_column_vec_double*P;

dataset=mlearning_mat_double_from_csv(DATASET_FILE_NAME,NULL,&dataset_header);
=======
mlearning_column_vec_double*P;

dataset=mlearning_mat_double_from_csv(DATASET_FILE_NAME);
>>>>>>> 887f9908761afa88b4c3556809a4a3cb4c75c6ca
if(dataset==NULL)
{
printf("Low memory\n");
return;
}

mlearning_mat_double_get_dimensions(dataset,&dataset_rows,&dataset_columns);

I_rows=dataset_rows;
I_columns=dataset_columns-1+1;

I=mlearning_mat_double_create_new(I_rows,I_columns);
if(I==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
return;
}

mlearning_mat_double_copy(I,dataset,0,1,0,0,dataset_rows-1,dataset_columns-2);

mlearning_mat_double_fill(I,0,0,I_rows-1,0,1.0);

m=mlearning_column_vec_double_from_csv(PARAMETERS_FILE_NAME,NULL,&model_header);
if(m==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
return;
}


P=mlearning_multiply_double_matrix_with_column_vector(I,m,NULL);
if(P==NULL)
{
printf("Low memory\n");
mlearning_mat_double_destroy(dataset);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(m);
mlearning_row_vec_string_destroy(model_header);
return;
}
results_file=fopen(RESULTS_FILE_NAME,"w");
if(results_file==NULL)
{
printf("Could not load results file\n");
mlearning_mat_double_destroy(dataset);
mlearning_mat_double_destroy(I);
mlearning_column_vec_double_destroy(m);
mlearning_row_vec_string_destroy(dataset_header);
mlearning_row_vec_string_destroy(model_header);
return;
}
fprintf(results_file,"input,actual_profit,predicted_profit\n");
for(r=0;r<dataset_rows;r++)
{
for(c=0;c<dataset_columns;c++)
{
fprintf(results_file,"%lf,",mlearning_mat_double_get(dataset,r,c));
}
fprintf(results_file,"%lf\n",mlearning_column_vec_double_get(P,r));
}
fclose(results_file);
}

int main(int argc,char*argv[])
{
if(argc!=4)
{
printf("Usage test_it.exe _ testing_dataset_file_name _ parameters_file_name _ result_file_name\n");
return 0;
}
DATASET_FILE_NAME=argv[1];
PARAMETERS_FILE_NAME=argv[2];
RESULTS_FILE_NAME=argv[3];
test_it();
printf("Result generated in %s\n",RESULTS_FILE_NAME);
return 0;
}