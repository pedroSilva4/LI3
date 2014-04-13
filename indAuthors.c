#include "indAuthors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




Indice* init(Indice* ind)
{

   Indice res[27];

   int i = 0;
   for(i;i<27;i++)
   {
   	res[i] = malloc(sizeof(Node));
   	res[i] = NULL;
   }

   ind = res;
   return ind ;
	
}

int hash(char* name)
{
	if(name[0] >='A' && name[0]<='Z')
		return name[0]-'A';
	else return 26;
}

int exists(Indice* ind ,char* nome)
{
	if(ind == NULL) return 0;

	int it = hash(nome);
	if(ind[it]==NULL) return 0;
	
	else
	{
		Indice aux =(Indice) malloc(sizeof(Node));
		aux = ind[it];
		while(aux)
		{
			if(!strcmp(aux->name,nome)) return 1;

			aux= aux->next;
		}
	}

return 0;
}

Indice add_sort(Indice branch, char* nome)
{
	Indice node = malloc(sizeof(Node));
				node-> name = strdup(nome);
				node->next = NULL;

	if(!branch)
	{
		
		branch = node;
		return branch;
	}
	else
	{	
		if(strcmp(branch->name,nome) > 0)
		{
			node->next = branch;
			branch = node;
			return branch;
		}
		if(strcmp(branch->name,nome) < 0)
		{
			if(!branch->next)
			{	
					branch->next = node;
					return branch;
			}
			else
			{
				branch->next = add_sort(branch->next,nome);
				return branch;
			}
		}
		

	
	}

	return branch;
	
}

Indice* addToInd(Indice* ind , char* nome)
{

	int it = hash(nome);
	if(!ind[it])
	{
		Indice aux2 = malloc(sizeof(Node));
		
		
		aux2->name = strdup(nome);
		aux2->next = NULL;
		//printf(" dont exists\n");
		ind[it] = aux2;
		//printf("inserted\n");
	}
	else
	{
		//printf("exists\n");
		ind[it] = add_sort(ind[it], nome);
	}


//printf("%s\n",nome);
return ind;
}


Indice* add_ArrayToInd(Indice* ind, char* arr[], int size)
{
	int i = 0;
	while(i<=size)
	{
		ind = addToInd(ind,arr[i]);
		i++;
	}

	return ind;
}

void printIndice(Indice* ind)
{
	printf("::Indice Autores::\n");
	Indice* aux = ind ;
	int i = 0;
	while(i<27)
	{
		
		Indice aux2 = malloc(sizeof(Node));
		aux2= aux[i];
		while(aux2)
		{
			printf("%d -->%s\n", hash(aux2->name),aux2->name);
			aux2 = aux2->next;
		}
		
	
	i++;
	}
}
/*
int main()
{
char* nomes[21] ={"\0"};
 nomes[0] = strdup("Ana"); 
 nomes[1] = strdup("Pedro");
 nomes[2] = strdup("Jose");
 nomes[3] = strdup("Tone");
nomes[4] = strdup("Bna"); 
 nomes[5] = strdup("Cedro Pereira");
 nomes[6] = strdup("Dose");
 nomes[7] = strdup("Eone");
 nomes[8] = strdup("Fna"); 
 nomes[9] = strdup("Hedro");
 nomes[10] = strdup("Cane");
 nomes[11] = strdup("Cne");
 nomes[12] = strdup("Cna"); 
 nomes[13] = strdup("Medro");
 nomes[14] = strdup("Nse");
 nomes[15] = strdup("Cone");
 nomes[16] = strdup("Qna"); 
 nomes[17] = strdup("Redro");
 nomes[18] = strdup("Sose");
 nomes[19] = strdup("Carla");

nomes[20] = strdup("Carla");


Indice* top= malloc(27*sizeof(Node));
int i = 0;
while(i<27)
{
	top[i] = malloc(sizeof(Node));
	top[i] =NULL;
	i++;
}



int k = 0;
int j = 0 ;

top = add_ArrayToInd(top,nomes,20);

printIndice(top);
	return 1;
}
*/