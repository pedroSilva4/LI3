#ifndef INDAUTHORS_H_INCLUDED
#define INDAUTHORS_H_INCLUDED



typedef struct indNode
{
	char* name;
	struct indNode *right;
	struct indNode *left;

}*Indice, Node;

Indice* initInd(Indice*);
Indice* addToInd(Indice*,char*);
void printIndice(Indice*);


#endif
