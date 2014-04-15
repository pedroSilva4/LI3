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


void co_autoYear(Catalog catalog,char* nome)
{
		if(!catalog) return ;

			if(!strcmp(catalog->author,nome))
			{
				Relations rel = catalog->relations;
				while(rel)
				{
					printf("%s, ", rel->name );
					rel  = rel->next;
				}
				return;
			}
			if(strcmp(catalog->author,nome)< 0)
			{
				co_autoYear(catalog->right,nome);
			}
			if(strcmp(catalog->author,nome)> 0)
			{
				co_autoYear(catalog->left,nome);
			}

}

void printCo_autores(Catalog* catalog,char* nome)
{
	printf("Os Co-autores de %s são\n",nome);
	printf(":::Co-autores:::\n");

	int i = 0;
	while(i<56)
	{
		if(catalog[i])
		{
			co_autoYear(catalog[i],nome);
		}
		i++;
	}
	printf("\n====================\n");
}
