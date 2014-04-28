#include <stdlib.h>
#include <stdio.h>
#include "../Headers/catalog.h"
#include <string.h>





Catalog* catInit(Catalog* catalog)
{
	Catalog* cata = malloc(56 * sizeof(cNode));

	int i;
	for(i=0;i<56;i++)
	{
	cata[i] = NULL;
	}
catalog = cata;
return catalog;
}


int catHash(int year)
{
	int res = year-1960;

	if(res>55)
		return 55;
	if(res<0)
		return 55;/*posicao 55 (ultima do array) fica com as pubs que sejam anteriores a 1960 e posteriores a 2014*/

	return res;
}

int existsRel(char*nome,Relations* rel)
{	int res = 0;
		Relations aux = *rel;
		while(aux)
		{
			if(!strcmp(nome,aux->name))
			{

				aux->ntimes++;
				res=1;
				return res;
			}
			aux = aux->next;
		}
return res;
} 

void addRelations(Relations* rel,char* nome,char** relations,int na)
{
	if(! *rel)
		{
			
			Relations new = NULL;
			int i = 0;
			if(!relations){
				
				*rel = NULL;
				return;
			}

			while(i<na)
			{
				if(strcmp(relations[i],nome) !=0 )
				{
					
					Relations rel_null = malloc(sizeof(rNode));
					rel_null->name = malloc(strlen(relations[i])+1);
					rel_null->name = strcpy(rel_null->name , relations[i]);
					rel_null->ntimes = 1;
					rel_null->next = new;
					new = rel_null;

				}
				
			i++;

			}
			*rel = new;
		return;
		}

	else
	{

		int i = 0;
			while(i<na)
			{
				if(strcmp(relations[i],nome) !=0 )
				{
					if(!existsRel(relations[i],rel)){
					Relations relaux = malloc(sizeof(rNode));
					relaux->name = malloc(strlen(relations[i])+1);
					relaux->name = strcpy(relaux->name , relations[i]);
					relaux->ntimes  = 1;
					relaux->next = *rel;
					*rel = relaux;
				}
				}
			i++;
			}

	}
}

Catalog placeAuthor(Catalog branch,char* nome, char** nomes,int na)
{
	if(!branch)
	{
	Catalog node = malloc(sizeof(cNode));
	node->author = malloc(strlen(nome)+1);
	node->author = strcpy(node->author,nome);
	node->np = 1;
	node->relations = NULL;
	addRelations(&node->relations,nome,nomes,na);
	node->right = NULL;
	node->left  = NULL;
	branch = node;
	}

	else
	{
		if(strcmp(branch->author,nome)>0)
		{
			branch->left = placeAuthor(branch->left,nome,nomes,na);
		}
		else{
				if(strcmp(branch->author,nome)<0)
				{
					branch->right = placeAuthor(branch->right,nome,nomes,na);
				}

				else 
				{   
					 if(!strcmp(branch->author,nome))
						{ 
							branch->np++;
							addRelations(&branch->relations,nome,nomes,na);
						}
		
				}
			}
	}

return branch;
}

Catalog* add(Catalog* catalog,  int year, char** nomes, int na)
{
	int ind = catHash(year);
	int i = 0;
	
	for(i;i<na;i++)
	{
		catalog[ind] = placeAuthor(catalog[ind],nomes[i],nomes,na);
	}
	
	return catalog;
}

void printCatalogBranch(Catalog branch)
{
	if(branch)
	{

			printCatalogBranch(branch->left);
			printf("=======PUBLICAÇÂO=======\n");
			printf("%s\n",branch->author);
			printf("%i\n",branch->np);
			
			printf("Relations\n");
			Relations rel = branch->relations;
			while(rel)
			{
			printf("+===============+\n");
			printf("%s\n",rel->name);
			printf("%i\n",rel->ntimes);
			printf("+===============+\n");
				rel = rel->next;
			}
			printf("======================\n");
			printCatalogBranch(branch->right);
	}


}

void printCatalog(Catalog* catalog)
{
	

	

		printf("::Catalogo Autores::\n");
	 
		int i = 0;
		while(i<56)
		{
			printf("::ANO %d::\n",i+1960);
			printCatalogBranch(catalog[i]);	
			i++;
		}
	
}
