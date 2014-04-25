#include "../Headers/indiceHandler.h"
#include "../Headers/catalog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Names getNamesBR(Indice indice, Names names)
{

	if(indice)
	{	
			names = getNamesBR(indice->left,names);
			Names new  = NULL;
			new = malloc(sizeof(rNode));
			new->name = malloc(strlen(indice->name)+2);
			new->name = strcpy(new->name, indice->name);
			new->ntimes = 0;
			new->next = names;
			names  = new;
			names = getNamesBR(indice->right,names);	
	}
	
return names;
}


Names getIndNames(Indice* indice,Names names)
{
	int i = 0;
	Names new = NULL;
	while(i<28)
	{
		if(indice[i])
		new = getNamesBR(indice[i],new);
	i++;
	}
	
	names =new;
return names;
}


void printNamesLetter(Indice indice,int *  n,int * c)
{
	
	if(indice)
	{
		
		printNamesLetter(indice->left,n,c);
		int g = *n+1;
		int k = *c+1;
		if(k<= 2)
		{
		printf("=> %s\t",indice->name);
		}
		else
		{
			printf("=> %s\n",indice->name);
			k= 0;
		}
		if(g>=60)
		{
			g=0;
			char buff[10];
			printf("\nPress any key to continue ...\n");
			fgets(buff,strlen(buff)+1,stdin);
		}
		*n = g;
		*c = k;
		printNamesLetter(indice->right,n,c);
		
	}
	
}

void averageLbranch(Indice branch,char** bigger, char** smaller , float * sum,int * nn)
{
	
	
	char* big  =NULL;
	if(branch)
	{
		int len = 0;
		
		averageLbranch(branch->left,bigger, smaller,sum,nn);
		len = (float) strlen(branch->name);

		if(len > strlen(*bigger)){
			
			big = malloc(strlen(branch->name)+1);
			big = strcpy(big,branch->name);
			*bigger = big;
		}
		if(len<strlen(*smaller))
			*smaller = branch->name;

		*sum += len;
		*nn+= 1;
	 	averageLbranch(branch->right,bigger,smaller,sum,nn); 
	}
	
}

void averagelength(Indice* indice)
{
	char* bigger =" ";
	char* smaller ="aaaaaaaaaaaaaaaaaaaa";
	float sum = 0;
	int nn = 0;
	int i = 0;
	while(i<28)
	{
		averageLbranch(indice[i],&bigger,&smaller,&sum,&nn);
		i++;
	}

	printf("Biggest Name is : %s\n", bigger);
	printf("Smallest Names is: %s\n", smaller);

	float mean = sum /(float) nn;
	printf("Average Name Length is : %f characters\n",mean );
}

int existsAuthor(Indice ind, char* name)
{
	int res = 0;
	if(ind)
	{
		res+= existsAuthor(ind->left,name);
		if(!strcmp(name,ind->name)) res = 1;
		res+= existsAuthor(ind->right,name);
		return res;
	}
	
}