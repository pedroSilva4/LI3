#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/indAuthors.h"
#include "Headers/parser.h"
#include "Headers/catalog.h"
#include "Headers/catalogHandler.h"
#include "Headers/indiceHandler.h"
#include "Headers/stats.h"
#include "Headers/statsHandler.h"


void printMenu()
{
	printf("\t+======GESTAUTS======+\n");
		printf("\t      +==Menu==+\n");
		printf("1 - Total de publicações por ano\n");
		printf("2 - Publicações do autor no ano  \n");
		printf("3 - Autores que publicaram a Solo\n");
		printf("4 - Tabela de Artigos\n");
		printf("5 - Nomes de Autores por 1ª letra\n");
		printf("6 - Total de Publicações entre\n");
		printf("7 - Co-autores\n");
		printf("8 - Autores que publicaram em todos os anos\n");
		printf("9 - Tabela com todas as Publicações com X autores\n");
		printf("10 - CSV com toda a informação de Publicações\n");
		printf("11 - Autores com maior numero de Publicações\n");
		printf("12 - Percentagem de publicações num ano\n");
		printf("13 - Media dos tamanhos dos nomes dos Autores\n");



	printf("\nARQUITETURA DE COMANDO: N;ARGS[1];ARGS[2];ARGS[3];...\n");
}


int isInt(char* str)
{	int i= 0;
	int res = 1;
	while(str[i]!= '\0')
	{
		if(str[i]>='0' && str[i]<='9')
			i++;
		else return 0;
	}
	return res;
}






int main(int argc,char** argv)
{
	if(argc!= 2)
	{
		printf("Wrong arguments!\nSintax: GESTAUTS 'file_path'\n");
		return 1;
    }
    /*time_t seconds = time(NULL);*/
    int entradas = 0;
	int menor_ano = 2015;
	int maior_ano = 0;
	int autores = 0;
	char *filename = argv[1];
	FILE* fl = fopen(filename,"a+");
	int read;
	char * line = NULL;
	size_t len = 0;
	int ano;
	Indice* indice;
	int i = 0;
	indice = initInd(indice); 
	Catalog * catalog;
	catalog = catInit(catalog);
	Stats* stats;
	stats = initStat(stats);

	while ((read = getline(&line, &len, fl)) != -1) 
	{
		int nap= 0;
		char** nomes;
		lineParser(line,&autores, &ano,&nap,&nomes); 

    	if(ano > maior_ano)
    		maior_ano = ano;

    	if(ano < menor_ano)
    		menor_ano = ano;
 
		catalog = add(catalog,ano,nomes,nap); 
		stats = addPub(stats, ano, nap);

		while(nap>0)
		{
 			indice = addToInd(indice ,nomes[nap-1]);
			nap--;
		}
		entradas++;
    	free(nomes);
    	len= 0;
	}
	printf("Ficheiro: %s\n", filename);
	printf("Publicaçoes: %d\n",entradas );
	printf("Numero total de autores: %d\n",autores );
	printf("Intervalo de anos: [%d-%d]\n", menor_ano,maior_ano);
	printf("=========================\n=========================\n");
	/*time_t seconds2 = time(NULL);
	/*printf("inicialização durou :: %ld segundos\n", (seconds2-seconds) );*/


	printMenu();
	int flag=1;
	while(flag)
	{
		i=0;
		char buff[100];
		char* delims = ";\n";
		printf(">>");
		fgets(buff, sizeof(buff), stdin);
	
		if(buff[0]!='\n' && buff[0]!=' ')
		{
			char* args[10];
			args[0] = strtok( buff, delims );
		
			while( args[i] != NULL && strcmp(args[i],"\n") ) 
			{
    			i++;
    			args[i] = strtok( NULL, delims );
			}

			if(isInt(args[0]))
			{
				int op = atoi(args[0]);
				int narg = i;/* number of arguments comand included*/
				switch (op)
				{
					case 1 :
					{
						if(narg != 1)
						{
							printf("wrong arguments\n Command :: >> 1");
							break;
						}
						else
						{
							table_printAll(stats);
							break;
						}
					}
					case 2 :
					{
						if(narg!= 3 || !isInt(args[1]))
						{

							printf("wrong arguments\n Command :: >> 2;\"year\";\"author\"\n");
							break;
						}
						else
						{	/*verificar se o autor existe*/
							if(existsAuthor(indice[hash(args[2])], args[2]))
							{
							/*se existe fazer*/
								int year = catHash(atoi(args[1]));
								int np = yearpublications(catalog[year],args[2]);
								printf("O Autor %s publicou %d vezes no ano %d\n", args[2],np,atoi(args[1]));
								break;
							}
							else
							{
								printf("Author %s does not exist\n", args[2]);
								break;
							}
						}
					}
				
					case 3 :
					{
						if(narg != 1)
						{
							printf("Wrong arguments\n Command :: >> 3\n");
							break;
						}
						else
						{
							soloPublishers(catalog);
							break;
						}
					}
				
					case 4:
					{
						if(narg!=2)
						{

							printf("wrong arguments\n Command :: >> 4;\"Autor\"\n");

							
							break;
						}
						else
						{
							/*ver se autor existe*/
							if(existsAuthor(indice[hash(args[1])], args[1]))
							{
								table_pubsByYear(catalog,args[1],menor_ano,maior_ano);
								break;
							}
							else
							{
								printf("Author %s does not exist\n",args[1]);
								break;
							}
						}
					}
		
					case 5:
					{	

						if(narg!=2)
						{
							printf("wrong arguments\n Command :: >> 5;\"Letter\"\n");
							break;
						}
						else
						{					
							printNamesLetter(indice[hash(args[1])]);
							printf("\n");
							break;
						}	
					}
					case 6:
					{
						if(narg!=3 || !isInt(args[1]) || !isInt(args[2]))
						{
							printf("Wrong arguments\n Command :: >> 6;\"Year1\" \"Year2\"\n");
							break;
						}
						else
						{
							printf("Numero de publicações entre [%d,%d]:\n%d\n",atoi(args[1]), atoi(args[2]), pubsInterval(stats, atoi(args[1]), atoi(args[2])));
							break;
						}
					}

					case 7:
					{
						/*det co-auotres*/
						if(narg != 2)
						{

							printf("wrong arguments\n Command :: >> 7;\"Autor\"\n");

							break;
						}
						else
						{
							if(existsAuthor(indice[hash(args[1])], args[1]))
							{
								printCo_autores(catalog,args[1]);
								break;
							}
							else
							{
								printf("Author %s does not exist\n",args[1]);
								break;
							}
						}
					}
				
					case 8:
					{ 
						if(narg!=3 || !isInt(args[1]) || !isInt(args[2]))
						{
							printf("wrong arguments\n Command :: >> 8;\"year1\";\"year2\" \n");
							break;
						}
						else
						{
							pubEveryYear(catalog,atoi(args[1]),atoi(args[2]));
							/*printf("correu bem\n");*/
							break;
						}
					}
				
					case 9:
					{
						if(narg!=3 || !isInt(args[1]))
						{
							printf("Wrong arguments\n Command :: >> 9;\"year\";\"filename\"\n");
						break;
						}
						else
						{
							table_printToThree(stats, atoi(args[1]), args[2]);
							break;
						}
					}

					case 10:
					{
						if(narg!=1)
						{
							printf("Wrong arguments\n Command :: >> 10\n");
							break;
						}
						else
						{
							tableCSV(stats);
							break;
						}
					
					
					
					}

					case 11:
					{
						if(narg!=2 || !isInt(args[1]))
						{
							printf("Wrong arguments\n Command :: >> 11;\"N authors\"\n");
							break;
						}
						else
						{
							Names names  =NULL;
							names = getIndNames(indice,names);
						 	int n = atoi(args[1]);
							n_authors(catalog,names,n);
							/*lista dos N autores com maior numero de publicaçoes*/
							break;
						}
					}

					case 12:
					{
						if(narg!=3 || !isInt(args[1]))
						{
							printf("Wrong arguments\n Command :: >> 12;\"Year\";\"Author\"\n");
							break;
						}
						else
						{
							if(existsAuthor(indice[hash(args[2])], args[2]))
							{
								int ind = catHash(atoi(args[1]));
								int totalpubs = totalPubsYear(stats, atoi(args[1]));
								int authorpubs = yearpublications(catalog[ind], args[2]);
								float res = ((float)authorpubs / (float)totalpubs)*100;
								printf("Percentagem de publicações do autor %s no ano %d:\n%f\n", args[2], atoi(args[1]), res);
								break;
							}
							else
							{
								printf("Author %s does not exist\n",args[2]);
								break;
							}
						}
					}

					case 13:
					{
						if(narg!=1)
						{
							printf("Wrong arguments\n Command :: >> 13\n");
							break;
						}
						else
						{
							averagelength(indice);
							break;
						}
						
					}

					default: 
					{		
						printf("Command number %d does not exist\nChoose a number from Menu\n",op);
						break;
					}
				}
			}
			else 
			{
				if(!strcmp(args[0],"quit")) return 0;

				if(!strcmp(args[0],"help")) printMenu();
			
				else
				{
					printf("Command %s does not exist\nChoose a number from Menu\n",args[0]);
				}
			}
		}
	}



fclose(fl);
free(indice);
free(catalog);

return 0;
}
