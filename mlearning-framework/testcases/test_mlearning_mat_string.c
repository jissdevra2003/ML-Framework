#include<mlearning_matrix.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
index_t r,c;
char *str;
mlearning_mat_string*matrix;
dimension_t rows,columns;
matrix=mlearning_mat_string_from_csv("insurance.csv");
if(matrix==NULL)
{
printf("Unable to load insurance.csv\n");
return 0;
}

mlearning_mat_string_get_dimensions(matrix,&rows,&columns);
for(r=0;r<rows;r++)
{
for(c=0;c<columns;c++)
{
mlearning_mat_string_get(matrix,r,c,&str);
if(str!=NULL)
{
printf("%s ",str);
free(str);
}
}
printf("\n");

}
mlearning_mat_string_destroy(matrix);
return 0;
}