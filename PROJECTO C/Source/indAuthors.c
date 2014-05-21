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

/*int main()
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
 nomes[15] = strdup("Carla");
 nomes[16] = strdup("Zeca"); 
 nomes[17] = strdup("Cona");
 nomes[18] = strdup("Dickson");
 nomes[19] = strdup("ANALIDE");

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

//printf("ainda imprime\n");
for(k = 0; k<21;k++){
top = addToInd(top,nomes[k]);
//printf("%d\n", k);
}
//printf("ainda imprime\n");
printIndice(top);
	return 1;
}
*/