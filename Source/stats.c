#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/stats.h"


Stats* initStat(Stats* stats)
{
	Stats* stat = (Stats * ) malloc(56 * sizeof(sNode));
	int k;
	for(k=0; k<56; k++)
	{
		stat[k] = NULL;
	}
	stats = stat;
	return stats;
}


int statHash(int year)
{
	int res = year - 1960;
	if (res > 55)
		res = 55;
	return res;
}

int yearFromHash(int hashYear)
{
	int res = hashYear + 1960;
	return res;
}

void addSorted(Stats* branch, Stats node)
{
	Stats temp = *branch;
	if(!*branch)
	{
		*branch = node;
		
	}
	else 
	{
		if(temp->numAut < node->numAut)
		{
			addSorted(&temp->right,node);
		}
		else
		{
			if(temp->numAut > node->numAut)
			{
				addSorted(&temp->left,node);
			}
			else
			{
				if(temp->numAut == node->numAut)
				{
					(*branch)->numPub++;
				}
			}
		}
	}		
}


Stats* addPub (Stats* stat, int year, int nAut)			/* Adiciona stats de uma publication */
{
	int hYear = statHash(year);
	Stats temp = malloc(sizeof(sNode));
	temp->numAut = nAut;
	temp->numPub = 1;
	temp->left = NULL;
	temp->right = NULL;
	addSorted(&stat[hYear], temp);
	return stat;
}

int totalPubsBranch(Stats stat)
{
	if(!stat)
	{
		return 0;
	}
	return stat->numPub + totalPubsBranch(stat->left) + totalPubsBranch(stat->right);
}

int totalPubsYear(Stats* stat, int year)			/* Retorna total de publicações no ano dado */
{
	int hYear = statHash(year);
	return totalPubsBranch(stat[hYear]);
}


void printBranchStats(Stats stat)
{
	if(stat)
	{
		printBranchStats(stat->left);
		printf("Publicações com %d autor(es): %d\n", stat->numAut, stat->numPub);
		printBranchStats(stat->right);
	}
}


