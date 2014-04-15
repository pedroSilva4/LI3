#include <stdlib.h>
#include <stdio.h>
#include "catalog.h"
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
					rel_null->name = strdup(relations[i]);
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

int existsauthor(Catalog* branch,char* nome,char** rel,int na)
{
	int res = 0;
	Catalog aux = *branch;
	
	
	while(aux)
	{
		
		if(!strcmp(aux->author,nome))
		{
			aux->np++;
			addRelations(&aux->relations,nome,rel,na);
			return 1;
		}
		aux = aux->next;
	} 
	return res;
}

Catalog placeAuthor(Catalog branch,char* nome,char** relations,int na)
{
	if(!branch)
	{
		
		Catalog br_null = malloc(sizeof(cNode));
		br_null->author = strdup(nome);
		br_null->np  =1;
		br_null->relations =NULL;
		addRelations(&br_null->relations,nome,relations,na);
		br_null->next = branch;
		branch = br_null;
		
		return branch;
	}
	else
	{
		

		//verificar se o autor ja existe na estrutura
		if(!(existsauthor(&branch , nome,relations,na)))
		{
			
			Catalog aux = malloc(sizeof(cNode));
			aux->author = strdup(nome);
			aux->np=1;
			aux->relations =NULL;

			addRelations(&aux->relations,nome,relations,na);

			aux->next =branch;
			branch = aux;
			return branch;
		}
		//existsauthor
		//caso exista incrementar o seu numero de obras e os seus co-autores
		
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

/*
int main()
{
	Catalog* cata;

	cata = init(cata);
char* nomes[] = {"ola","asd","tone","quim"};
char* nomes2[] = {"asd","tone","quim"};



cata = add(cata,2012,nomes,4);
cata  = add(cata,2012,nomes2,3);

int i=0;
for(;i<56;i++)
{
	if(cata[i])
	{
		printf(":::::::ANO %d::::::::\n", i+1960);
		while(cata[i]){
		printf("%s\n",cata[i]->author );
		printf("%d\n",cata[i]->np);
		while(cata[i]->relations)
		{
			printf("rel :: %s ++ ntimes:: %d\n",cata[i]->relations->name,cata[i]->relations->ntimes);
			cata[i]->relations = cata[i]->relations->next;
		}
		cata[i] = cata[i]->next;
		}
	}
}

return 1;


}
*/