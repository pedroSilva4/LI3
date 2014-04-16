#ifndef _CATHANDLER_
#define _CATHANDLER_

#include "catalog.h" 


int yearpublications(Catalog, char*);
void soloPublishers(Catalog* catalog);
void table_pubsByYear(Catalog*,char*,int,int);
void printCo_autores(Catalog*,char*);
void pubEveryYear(Catalog* catalog, int year1, int year2);
void n_authors(Catalog* catalog,Names ,int n);
#endif