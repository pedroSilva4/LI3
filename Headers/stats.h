#ifndef _STATS_
#define _STATS_

typedef struct stats
{
	int numAut;		/*Numero de autores em cada publicacao*/
	int numPub;		/*Numero de publicacoes com mesmo numAut*/
/*	int year;		*/
	struct stats *left;
	struct stats *right;

}*Stats, sNode;

Stats* initStat(Stats*);
Stats* addPub(Stats*,int,int);
void printStats(Stats*);
int totalPubsYear(Stats*,int);
int statHash(int);
int PubsInterval(Stats*,int,int);
void table_printAll(Stats*);

#endif
