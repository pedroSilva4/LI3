#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Headers/catalogHandler.h"
#include "../Headers/catalog.h"



int yearpublications(Catalog catalog, char* nome)
{
		if(!catalog) return 0;

			if(!strcmp(catalog->author,nome))
			{
				return catalog->np;
			}
			if(strcmp(catalog->author,nome)< 0)
			{
				return yearpublications(catalog->right,nome);
			}
			if(strcmp(catalog->author,nome)> 0)
			{
				return yearpublications(catalog->left,nome);
			}

}

int solo(Catalog catalog)
{
	int res = 0;
	if(catalog)
	{
	res += solo(catalog->left);
	if(catalog->relations == NULL)
	{
		res++;
	}
	res+=solo(catalog->right);
	}
	return res;
}


void soloPublishers(Catalog* catalog)
{
	if(!catalog)
		return;
	else
	{
		int total = 0;
		int i = 0;
		while(i<56)
		{
			if(catalog[i]){

				
				int res = solo(catalog[i]);
				total += res;
				
			}
			i++;
		}
		printf("Numero total :: %d\n", total );
	}
}

void table_pubsByYear(Catalog* catalog,char* nome,int menor_ano,int maior_ano)
{
	int i = catHash(menor_ano);
	
	while(i<=catHash(maior_ano))
	{
		if(i == catHash(maior_ano))
		{
			printf("+------+------+\n");
			printf("| %d | %d   |\n",i+1960,yearpublications(catalog[i],nome));
			printf("+------+------+\n");
		}
		else
		{
			printf("+------+------+\n");
			printf("| %d | %d   |\n",i+1960,yearpublications(catalog[i],nome));
		}
		i++;
	}
}



typedef struct snames
{
	char* name;
	int ntimes;
	struct snames *left;
	struct snames *right;

}*Tnames,tNode;


Tnames insertTnames(Tnames names,char* name,int ntimes)
{
	if(!names)
	{
		names = malloc(sizeof(tNode));
		names->name =malloc(strlen(name)+1);
		names->name = strcpy(names->name,name);
		names->ntimes = ntimes;
		names->left = NULL;
		names->right = NULL;
		return names;
	}
	else
	{
		if(strcmp(names->name,name)< 0)
				names->left = insertTnames(names->left,name,ntimes);
		else
			if(strcmp(names->name,name) > 0)
			{
				names->right = insertTnames(names->right,name,ntimes);
			}
			else
			{
				names->ntimes += ntimes;
			}
	}
	return names;

}

Tnames co_autoYear(Catalog catalog,char* nome,Tnames names)
{
		if(catalog){

			if(!strcmp(catalog->author,nome))
			{
				Relations rel = catalog->relations;
				while(rel)
				{
					
						names  = insertTnames(names,rel->name,rel->ntimes);
					
					
					rel  = rel->next;
				}
				
			}
			if(strcmp(catalog->author,nome)< 0)
			{
				names = co_autoYear(catalog->right,nome,names);
			}
			if(strcmp(catalog->author,nome)> 0)
			{
				names = co_autoYear(catalog->left,nome,names);
			}
		}

return names;
}

Tnames mostTimes(Tnames names, Tnames aux)
{
	if(!aux)
	{
		aux = malloc(sizeof(tNode));
		aux->name  = malloc(strlen(names->name)+1);
				aux->name = strcpy(aux->name,names->name);
				aux->ntimes = names->ntimes;
				aux->left = NULL;
				aux->right  =NULL;
	}
	if(names)
	{
		aux = mostTimes(names->left,aux);
		if(aux)
		{	
			if(names->ntimes > aux->ntimes)
			{
				
				aux->name  = malloc(strlen(names->name)+1);
				aux->name = strcpy(aux->name,names->name);
				aux->ntimes = names->ntimes;
				aux->left = NULL;
				aux->right = NULL;

			}
			if(names->ntimes == aux->ntimes)
			{
				if(strcmp(aux->name,names->name))
				{
				char * inc = malloc(strlen(aux->name) + 2 + strlen(names->name) +1 );
				inc =strcpy(inc,aux->name);
				inc = strcat(inc,", ");
				inc = strcat(inc,names->name);
				aux->name = inc;
				}
			}
		}
		aux = mostTimes(names->right,aux);
	}
	return aux;
}

void printCo_autores(Catalog* catalog,char* nome)
{
	printf("O(s) Co-autor(es) de %s com mais publicações é(são)\n",nome);
	printf(":::Co-autor(es):::\n");
	Tnames names = NULL;

	int i = 0;
	while(i<56)
	{
		if(catalog[i])
		{
			names  = co_autoYear(catalog[i],nome,names);
		}
		i++;
	}

	
	Tnames aux =NULL;
	aux =  mostTimes(names,aux);

	printf("%s com %d publicação(ões)\n",aux->name,aux->ntimes );
	printf("====================\n");
}

Names getNames(Catalog branch,Names names)
{

	
	if(branch)
	{	
			names = getNames(branch->left,names);
			Names new  = NULL;
			new = malloc(sizeof(rNode));
			new->name = malloc(strlen(branch->author)+1);
			new->name = strcpy(new->name, branch->author);
			new->ntimes = 0;
			new->next = names;
			names  = new;
			
			names = getNames(branch->right,names);
		
		
		
	}
	
return names;
}

void pubEveryYear(Catalog* catalog, int year1, int year2)
{
	int ini = catHash(year1);
	int fim = catHash(year2);

	Names names = NULL;

	names = getNames(catalog[ini],names);

	int res= fim-ini + 1;

	Names aux =  names;
	while(aux)
	{
		int i = ini;
		while(i<=fim)
		{
			
			if(yearpublications(catalog[i],aux->name))
				aux->ntimes++;
			i++;
		}

		if(aux->ntimes==res)
			printf("%s, ",aux->name );

		aux= aux->next;
	}

	printf("\n");	
}


Names* top_n(Names* names, Names name, int n)
{
	Names aux = name;
	
	int np = aux->ntimes;
	int i = 0;
	int insInto = -1;
	int inserted = 0;
	while(i<n)
	{
		if(!names[i])
		{
			names[i] = malloc(sizeof(rNode));
			names[i] = aux;
			inserted = 1;
			break;
		}
		else
		{
			if(names[i]->ntimes< np){
				np = names[i]->ntimes;
				insInto = i;
			}
		}
		i++;
	}

	if(inserted==1)
		return names;
	
	if(insInto!=-1)
		names[insInto] = aux;
	
	return names;

}

void n_authors(Catalog* catalog,Names names,int n)
{
	Names aux = names;

	Names* res = malloc(n*sizeof(rNode));


	while(aux)
	{
		int i=0 ;
		while(i<56)
		{
			if(catalog[i])
			{
				aux->ntimes += yearpublications(catalog[i],aux->name);
				
			}
		  i++;
		}
		
	res = top_n(res,aux,n);

	aux = aux->next;
	}
	
	int i= 0;
	while(i<n)
	{
		printf("%s --> %d\n",res[i]->name,res[i]->ntimes);
		i++;
	}
}
/*
int main()
{
	return 1;
}
*/