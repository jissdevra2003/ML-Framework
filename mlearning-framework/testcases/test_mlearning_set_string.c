#include<mlearning_set.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
mlearning_set_string*set;
dimension_t set_size;
index_t i;
char*str;
set=mlearning_set_string_create_new();
mlearning_set_string_add(set,"Jiss");
mlearning_set_string_add(set,"Jiss");
mlearning_set_string_add(set,"Thomas");
mlearning_set_string_add(set,"Walter");
mlearning_set_string_add(set,"Jesse");
mlearning_set_string_add(set,"walter");
set_size=mlearning_set_string_get_size(set);
printf("Size of set is %u\n",set_size);
for(i=0;i<set_size;i++)
{
mlearning_set_string_get(set,i,&str);
if(str!=NULL)
{
printf("%s\n",str);
}
free(str);
}

mlearning_set_string_destroy(set);
return 0;
}