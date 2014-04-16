#ifndef _STATHANDLER_
#define _STATHANDLER_

#include "stats.h"

void table_printAll(Stats*);
int PubsInterval(Stats*,int,int);
void table_printToThree(Stats*, int, char*);
void tableCSV(Stats*);


#endif
