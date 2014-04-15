#ifndef INDAUTHORS_H_INCLUDED
#define INDAUTHORS_H_INCLUDED



typedef struct indNode
{
	char* name;
	struct indNode *next;

}*Indice, Node;


void init(Indice* );

Indice* addToInd(Indice*, char*);

Indice* add_ArrayToInd(Indice* ind, char* arr[], int size);

char* printInd(Indice*,int);



#endif
