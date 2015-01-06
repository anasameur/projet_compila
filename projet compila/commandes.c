#include<stdio.h>
#include<stdlib.h>

void _create_new_tab(char *new_name){
FILE *dic,*new_file; int i= 10;
char name[100];
dic  = fopen("dictionary","w+");
while(fscanf(dic,"%s",name) != EOF){
	printf("name : %s\n",name);
	if(strcmp(name,new_name) == 0)
		printf("table already exists\n");
	}
fprintf(dic,"%s",new_name);
new_file = fopen(new_name,"w");
fclose(dic);
fclose(new_file);
}
		
