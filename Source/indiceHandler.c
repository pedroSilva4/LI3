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