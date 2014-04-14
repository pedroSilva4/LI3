#include "indAuthors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void init(Indice* indice)
{

Indice* res = (Indice * ) malloc(28*sizeof(Node));
indice = res;
	int ind = 0;
	while(ind<28)
	{
		indice[ind] = malloc(sizeof(Node));
		indice[ind] = NULL;
		ind++;
	}
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

void add_sort(Indice* branch, char* nome)
{
	Indice node = malloc(sizeof(Node));
				node-> name = strdup(nome);
				node->next = NULL;

	
		//*branch = node;
		
		Indice tail = *branch;
		Indice head = malloc(sizeof(Node));
		//head = NULL;
	
		while(tail && strcmp(tail->name,nome) < 0)
		{
			
			head = tail;

			tail = tail->next;
		}
		
		
		if(!head)
		{
			node->next = *branch;
			
		}

		else
		{
			head->next = node;
			node->next = tail;
		}
	

	
	
}

Indice* addToInd(Indice* ind , char* nome)
{

	if(exists(ind,nome))
		return ind;

	int it = hash(nome);
	if(!ind[it])
	{
		Indice aux2 = malloc(sizeof(Node));
		aux2->name = strdup(nome);
		aux2->next = NULL;
		ind[it] = aux2;
	}
	else
	{
	add_sort(&ind[it], nome);
	}
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

printf("ainda imprime\n");
for(k = 0; k<21;k++){
top = addToInd(top,nomes[k]);
printf("%d\n", k);
}
printf("ainda imprime\n");
printIndice(top);
	return 1;
}
*/