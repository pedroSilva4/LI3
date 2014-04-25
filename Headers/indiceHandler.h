#ifndef _INDHANDLER_
#define _INDHANDLER_

#include "indAuthors.h"
#include "catalog.h"

Names getIndNames(Indice* indice,Names names);
void averagelength(Indice* indice);
void printNamesLetter(Indice indice,int*,int* );
int existsAuthor(Indice ind, char* name);
#endif