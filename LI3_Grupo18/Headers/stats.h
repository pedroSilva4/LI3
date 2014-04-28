#ifndef _STATS_
#define _STATS_

typedef struct stats
{
	int numAut;		/*Numero de autores em cada publicacao*/
	int numPub;		/*Numero de publicacoes com mesmo numAut*/
	struct stats *left;
	struct stats *right;

}*Stats, sNode;

Stats* initStat(Stats*);
Stats* addPub(Stats*,int,int);
int totalPubsYear(Stats*,int);
int statHash(int);
int yearFromHash(int);

#endif
