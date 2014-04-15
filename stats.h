#ifndef _STATS_
#define _STATS_

typedef struct stats
{
	char** nomes;
	int nap;		//Numero de publicacoes no ano
	int year;
	struct stats *next;

}*Stats, sNode;

#endif
