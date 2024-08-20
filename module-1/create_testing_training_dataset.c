//split the dataset into testing dataset(minor) , training dataset(major)
#include<stdio.h>
#include<mlearning_matrix.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
mlearning_mat_double*shuffled_matrix;
mlearning_mat_double*matrix;
mlearning_mat_double*test_matrix;
mlearning_mat_double*train_matrix;
dimension_t test_matrix_rows;
dimension_t train_matrix_rows;
dimension_t shuffled_matrix_rows,shuffled_matrix_columns;
char*dataset_file;
char*testing_file;
char*training_file;
int minor_percentage;
if(argc!=5)
{
printf("Usage : [create_testing_training_dataset.exe _ dataset_file_name _ testing_file_name _ training_file_name _ minor_percentage]\n");
return 0;
}
dataset_file=argv[1];
testing_file=argv[2];
training_file=argv[3];
minor_percentage=atoi(argv[4]);
if(minor_percentage<=0 || minor_percentage>50) 
{
printf("Invalid minor percentage\n");
return 0;
}
matrix=mlearning_mat_double_from_csv(dataset_file);
if(matrix==NULL)
{
printf("Unable to load testing/training files\n");
return 0;
}
shuffled_matrix=mlearning_mat_double_shuffle(matrix,7);
if(shuffled_matrix==NULL)
{
printf("Unable to load testing/training files\n");
mlearning_mat_double_destroy(matrix);
return 0;
}
mlearning_mat_double_get_dimensions(shuffled_matrix,&shuffled_matrix_rows,&shuffled_matrix_columns);

test_matrix_rows=(dimension_t)(minor_percentage*shuffled_matrix_rows)/100;
train_matrix_rows=shuffled_matrix_rows-test_matrix_rows;

test_matrix=mlearning_mat_double_create_new(test_matrix_rows,shuffled_matrix_columns);
if(test_matrix==NULL)
{
printf("Unable to load testing/training files\n");
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
return 0;
}

train_matrix=mlearning_mat_double_create_new(train_matrix_rows,shuffled_matrix_columns);
if(train_matrix==NULL)
{
printf("Unable to load testing/training files\n");
mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_mat_double_destroy(test_matrix);
return 0;
}

mlearning_mat_double_copy(test_matrix,shuffled_matrix,0,0,0,0,test_matrix_rows-1,shuffled_matrix_columns-1);
mlearning_mat_double_copy(train_matrix,shuffled_matrix,0,0,test_matrix_rows,0,shuffled_matrix_rows-1,shuffled_matrix_columns-1);

mlearning_mat_double_to_csv(test_matrix,testing_file);
mlearning_mat_double_to_csv(train_matrix,training_file);

mlearning_mat_double_destroy(matrix);
mlearning_mat_double_destroy(shuffled_matrix);
mlearning_mat_double_destroy(test_matrix);
mlearning_mat_double_destroy(train_matrix);
return 0;
}