#ifndef _CATALOG_
#define _CATALOG_

typedef struct rel	//estrura para relaçoes de autores
{
	char* name;
	int ntimes;
	struct rel *next;
}*Relations,rNode;


typedef struct entry
{
	char * author;
	int np;	//numero publicações desse autor nesse ano
	Relations relations;//autores com que publicou nesse ano
	struct entry * next;
}*Catalog,cNode;

Catalog * catInit(Catalog*);
Catalog * add(Catalog*,int,char**,int);


#endif