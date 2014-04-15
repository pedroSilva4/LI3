#ifndef _CATALOG_
#define _CATALOG_

typedef struct rel	/*estrura para relaçoes de autores*/
{
	char* name;
	int ntimes;
	struct rel *next;
}*Relations,rNode;


typedef struct entry
{
	char * author;
	int np;	/*numero publicações desse autor nesse ano*/
	Relations relations;/*autores com que publicou nesse ano*/
	struct entry * right;
	struct entry *left;
	
	
}*Catalog,cNode;

Catalog * catInit(Catalog*);
int catHash(int year);
Catalog * add(Catalog*,int,char**,int);
void printCatalog(Catalog *);


#endif