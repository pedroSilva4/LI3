#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/stats.h"
#include "../Headers/statsHandler.h"

void table_printAll(Stats* stat)					/* Imprime tabela de todos os anos e publicações por ano, 1 no menu */
{
	int j;
	printf("======================\n");
	printf("|Ano\t|Publicações\n");
	printf("======================\n");
	for(j=0; j<56; j++)
	{
		if(stat[j])
		{
		printf("|%d\t|%d\n", yearFromHash(j), totalPubsYear(stat, yearFromHash(j)));
		printf("======================\n");
		}
	}
}

int pubsInterval(Stats* stat, int small, int big)			/*Retorna intervalo entre dois anos*/
{
	int total = 0;
	while(small<=big)
	{
		total+=totalPubsYear(stat, small);
		small++;
	}
	return total;
}	

int numPubsAut(Stats stat, int num)
{
	if(!stat)
	{
		return 0;
	}
	if(stat->numAut == num)
	{
		return stat->numPub;
	}
	if(stat->numAut < num)
	{
		numPubsAut(stat->right, num);
	}else
	{
		numPubsAut(stat->left, num);
	}
}	



void table_printToThree(Stats* stat, int year, char* filename)
{
	int hYear = statHash(year);
	int j, pubs;
	FILE * pFile;
	pFile = fopen(filename, "w");
	Stats temp = stat[hYear];
	printf("==============================================\n");
	fprintf(pFile, "==============================================\n");
	printf("|Numero de Autores     |Numero de Publicações\n");
	fprintf(pFile, "|Numero de Autores     |Numero de Publicações\n");
	printf("==============================================\n");
	fprintf(pFile, "==============================================\n");
	for(j=1; j<4; j++)
	{
		pubs = numPubsAut(stat[hYear], j);
		printf("|%d                     |%d\n", j, pubs);
		fprintf(pFile,"|%d                     |%d\n", j, pubs);
		printf("==============================================\n");
		fprintf(pFile, "==============================================\n");
	}
	fclose(pFile);
}

void tableBranchCSV(Stats stat, int year, FILE * file)
{
	if(stat)
	{
		tableBranchCSV(stat->left, year, file);
		fprintf(file, "\"%d\",\"%d\",\"%d\"\n", year, stat->numAut, stat->numPub);
		tableBranchCSV(stat->right, year, file);	
	}
}


void tableCSV(Stats* stat)
{
	int k;
	FILE * file;
	file = fopen("Estatisticas.csv", "w");
	fprintf(file, "\"Ano\",\"#Autores\",\"#Artigos\"\n");
	for(k=0;k<56;k++)
	{
		tableBranchCSV(stat[k], yearFromHash(k), file);	
	}	
	fclose(file);

}
