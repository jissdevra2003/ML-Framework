#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mlearning_vector.h>
#include<mlearning_matrix.h>
#include<mlearning_encoder.h>
#include<mlearning_scale.h>
#include<mlearning_operations.h>
int main()
{
mlearning_row_vec_double*r_vec;
mlearning_column_vec_double*c_vec;
mlearning_mat_double*min_max_matrix;
double scaled_prediction;
double prediction;  //unscaled_prediction
// index_t i;
// dimension_t c_vec_size;
mlearning_column_vec_double*prediction_vector;
double min,max;
double age;
char gender;
double bmi;
double children;
char smoker;
char region1[15]="southwest";
char region2[15]="southeast";
char region3[15]="northwest";
char region4[15]="northeast";
char*region;
mlearning_row_vec_double*scaled_r_vec;
dimension_t min_max_rows,min_max_columns;



FILE*parameters_file_name;
printf("Enter age :");
scanf("%lf",&age);
fflush(stdin);
if(age<=0)
{
printf("Invalid age");
return 0;
}
printf("Enter gender :");
scanf("%c",&gender);
fflush(stdin);
if(gender!='m' && gender!='M' && gender!='f' && gender!='F')
{
printf("Invalid gender");
return 0;
}
printf("Enter Body Mass Index :");
scanf("%lf",&bmi);
fflush(stdin);
printf("Enter number of children :");
scanf("%lf",&children);
fflush(stdin);
printf("Smoker Yes/No ?");
scanf("%c",&smoker);
fflush(stdin);
if(smoker!='y' && smoker!='Y' && smoker!='N' && smoker!='n')
{
printf("Smoker enter only yes(y) and no(n)\n");
return 0;
}

printf("Region :");
region=(char*)malloc(sizeof(char)*30);
scanf("%s",region);
fflush(stdin);
if(strcmp(region,region1)!=0 && strcmp(region,region2)!=0 && strcmp(region,region3)!=0 && strcmp(region,region4)!=0)
{
printf("Invalid region , choose region from (southeast,southwest,northeast,northwest)\n");
return 0;
}
parameters_file_name=fopen("Insurance_model.csv","r");
if(parameters_file_name==NULL)
{
printf("Unable to load Insurance parameters file\n");
free(region);
return 0;
}
c_vec=mlearning_column_vec_double_from_csv("Insurance_model.csv");
if(c_vec==NULL)
{
printf("Low memory\n");
fclose(parameters_file_name);
free(region);
return 0;
}
r_vec=mlearning_row_vec_double_create_new(12);
if(r_vec==NULL)
{
printf("Low memory\n");
fclose(parameters_file_name);
mlearning_column_vec_double_destroy(c_vec);
free(region);
return 0;
}
mlearning_row_vec_double_set(r_vec,0,1.0);
mlearning_row_vec_double_set(r_vec,1,age);
if(gender=='M' || gender=='m')
{
mlearning_row_vec_double_set(r_vec,2,1);
mlearning_row_vec_double_set(r_vec,3,0);
}
else 
{
mlearning_row_vec_double_set(r_vec,2,0);
mlearning_row_vec_double_set(r_vec,3,1);
}
mlearning_row_vec_double_set(r_vec,4,bmi);
mlearning_row_vec_double_set(r_vec,5,children);
if(smoker=='y' || smoker=='Y')
{
mlearning_row_vec_double_set(r_vec,6,1);
mlearning_row_vec_double_set(r_vec,7,0);
}
else 
{
mlearning_row_vec_double_set(r_vec,6,0);
mlearning_row_vec_double_set(r_vec,7,1);
}

if(strcmp(region,region1)==0)
{
mlearning_row_vec_double_set(r_vec,8,1);
mlearning_row_vec_double_set(r_vec,9,0);
mlearning_row_vec_double_set(r_vec,10,0);
mlearning_row_vec_double_set(r_vec,11,0);

}
else if(strcmp(region,region2)==0)
{
mlearning_row_vec_double_set(r_vec,9,1);
mlearning_row_vec_double_set(r_vec,8,0);
mlearning_row_vec_double_set(r_vec,10,0);
mlearning_row_vec_double_set(r_vec,11,0);


}
else if(strcmp(region,region3)==0)
{
mlearning_row_vec_double_set(r_vec,10,1);
mlearning_row_vec_double_set(r_vec,8,0);
mlearning_row_vec_double_set(r_vec,9,0);
mlearning_row_vec_double_set(r_vec,11,0);

}
else 
{
mlearning_row_vec_double_set(r_vec,11,1);
mlearning_row_vec_double_set(r_vec,8,0);
mlearning_row_vec_double_set(r_vec,9,0);
mlearning_row_vec_double_set(r_vec,10,0);
}
//for testing contents of c_vec
// c_vec_size=mlearning_column_vec_double_get_size(c_vec);
// for(i=0;i<c_vec_size;i++)
// {
// printf("%lf , ",mlearning_column_vec_double_get(c_vec,i));
// }
min_max_matrix=mlearning_mat_double_from_csv("min_max.csv");
if(min_max_matrix==NULL)
{
printf("Low memory\n");
free(region);
mlearning_row_vec_double_destroy(r_vec);
mlearning_column_vec_double_destroy(c_vec);
return 0;
}
mlearning_mat_double_get_dimensions(min_max_matrix,&min_max_rows,&min_max_columns);
scaled_r_vec=mlearning_scale_row_vec_double_with_given_min_max(r_vec,0,11,min_max_matrix);
if(scaled_r_vec==NULL)
{
printf("Low memory\n");
free(region);
mlearning_row_vec_double_destroy(r_vec);
mlearning_column_vec_double_destroy(c_vec);
mlearning_mat_double_destroy(min_max_matrix);
return 0;
}

//  r_vec_size=mlearning_row_vec_double_get_size(r_vec);
//  for(i=0;i<r_vec_size;i++)
//  {
//  printf("%lf , ",mlearning_row_vec_double_get(scaled_r_vec,i));
//  }
prediction_vector=mlearning_multiply_double_row_vector_with_column_vector(scaled_r_vec,c_vec);
if(prediction_vector==NULL)
{
printf("Low memory\n");
free(region);
mlearning_row_vec_double_destroy(r_vec);
mlearning_column_vec_double_destroy(c_vec);
mlearning_mat_double_destroy(min_max_matrix);
mlearning_row_vec_double_destroy(scaled_r_vec);
return 0;
}
scaled_prediction=mlearning_column_vec_double_get(prediction_vector,0);
min=mlearning_mat_double_get(min_max_matrix,0,0);
max=mlearning_mat_double_get(min_max_matrix,1,0);
prediction=(scaled_prediction*(max-min))+min;
printf("Predicted(scaled) charges is %lf",prediction);
fclose(parameters_file_name);

free(region);
mlearning_row_vec_double_destroy(r_vec);
mlearning_column_vec_double_destroy(c_vec);
mlearning_mat_double_destroy(min_max_matrix);
mlearning_row_vec_double_destroy(scaled_r_vec);
mlearning_column_vec_double_destroy(prediction_vector);
return 0;
}