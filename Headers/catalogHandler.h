#ifndef _CATHANDLER_
#define _CATHANDLER_

#include "catalog.h" 


int yearpublications(Catalog, char*);
void soloPublishers(Catalog* catalog);
void table_pubsByYear(Catalog*,char*,int,int);
void printCo_autores(Catalog*,char*);

#endif