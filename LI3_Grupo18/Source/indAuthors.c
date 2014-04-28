#include "../Headers/indAuthors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




Indice* initInd(Indice* indice)
{

Indice* res = (Indice * ) malloc(28*sizeof(Node));

	int ind = 0;
	while(ind<28)
	{
		res[ind] = NULL;
		ind++;
	}
	indice = res;
	return indice;
}

int hash(char* name)
{
	if(name[0] >='A' && name[0]<='Z')
		return name[0]-'A';
	else
		if(name[0] >='a' && name[0]<='z')
			return name[0]-'a';
	
	else return 26;
}

void add_sort(Indice* branch, Indice node)
{
	Indice aux = *branch;
	if(!*branch)
	{
		*branch = node;
		
	}
	else 
	{
		if(strcmp(aux->name,node->name) < 0 )
		{
			
				add_sort(&aux->right,node);
		}
		else
		{
			if(strcmp(aux->name,node->name) > 0 )
			{
			
				add_sort(&aux->left,node);
			}
		}
	
	}		
}

Indice* addToInd(Indice* ind , char* nome)
{
	int it = hash(nome);

	Indice node = malloc(sizeof(Node));
				node-> name =(char*) malloc(strlen(nome)+1);
				node-> name = strcpy(node->name,nome);
				node->right = NULL;
				node->left = NULL;

	 add_sort(&ind[it], node);

return ind;
}

void printBranch(Indice ind)
{
 if(ind)
	{
			printBranch(ind->left);
			printf("%s\n",ind->name);
			printBranch(ind->right);
	}
	
}
void printIndice(Indice* ind)
{
	printf("::Indice Autores::\n");
	 
	int i = 0;
	while(i<27)
	{
			printBranch(ind[i]);	
			i++;
	}
}

