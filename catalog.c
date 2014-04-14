#include <stdlib.h>
#include <stdio.h>
#include "catalog.h"
#include <string.h>





void init(Catalog** catalog)
{
	Catalog* catlog = (Catalog*) malloc(56 * sizeof(cNode));
int i;
	for(i=0;i<56;i++)
	{
		catlog[i] = NULL;
	}

	*catalog = catlog;
} 

int hash(int year)
{
	int res = year-1960;

	if(res>55)
		return 55;

	 
	return res;
}

int exists(char*nome,Relations* rel)
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
void addRelations(Relations* rel,char* nome,char** relations)
{
	if(! *rel)
		{
			Relations new = NULL;
			int i = 0;
			while(relations[i])
			{
				if(strcmp(relations[i],nome) !=0 )
				{
					Relations rel_null = malloc(sizeof(rNode));
					rel_null->name = strdup(relations[i]);
					rel_null->ntimes = 1;
					rel_null->next = new;

					new = rel_null;
				}
			i++;
			}
		*rel= new;
		}

	else
	{

		int i = 0;
			while(relations[i])
			{
				if(strcmp(relations[i],nome) !=0 )
				{
					if(!exists(relations[i],rel)){
					Relations relaux = malloc(sizeof(rNode));
					relaux->name = strdup(relations[i]);
					relaux->ntimes  = 1;
					relaux->next = *rel;
					*rel = relaux;
				}
				}
			i++;
			}

	}
}

void placeAuthor(Catalog* branch,char* nome,char** relations)
{
	if(!catalog)
	{
		Catalog br_null = malloc(sizeof(cNode));
		br_null->author = strdup(nome);
		br_null->relations =NULL;
		addRelations(&br_null->relations,nome,relations);
		br_null->next = NULL;
		*branch = br_null;
	}
	else
	{
		//verificar se o autor ja existe na estrutura
		//existsauthor
		//caso exista incrementar o seu numero de obras e os seus co-autores

	}
}


void add(Catalog** catalog,  int year, char** nomes, int na)
{
	int ind = hash(year);
	int i = 0;
	for(i;i<nap;i++)
	{
		placeAuthor(&catalog[ind],nomes[i],nomes);
	}
}


int main()
{
	Catalog* cata;
	init(&cata);
int i;
//for(i=0;i<56;i++)
	//if(cata[i] == NULL) printf("lol\n");






Relations rel = NULL;

char* nomes[] = {"ola","asd","tone","quim"};

 addRelations(&rel,nomes[0],nomes);

 char* nomes2[] = {"asd","tone","quim"};

 addRelations(&rel,nomes[0],nomes2);

while(rel)
{
	printf("%s\n",rel->name);
	printf("%d\n",rel->ntimes);
	rel =rel->next;
}
	return 1;


}