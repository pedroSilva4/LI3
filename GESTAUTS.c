#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/indAuthors.h"
#include "Headers/parser.h"
#include "Headers/catalog.h"
#include "Headers/catalogHandler.h"
#include "Headers/indiceHandler.h"

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
	if(argc!= 2){
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

	while ((read = getline(&line, &len, fl)) != -1) {
	int nap= 0;
	char** nomes;
	lineParser(line,&autores, &ano,&nap,&nomes); 

    if(ano > maior_ano)
    	maior_ano = ano;

    if(ano < menor_ano)
    	menor_ano = ano;
 
	catalog = add(catalog,ano,nomes,nap); 

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
					printf("Imprimir da tabela de stats\n");	
					break;
				}
				case 2 :
				{
					if(narg!= 3 || !isInt(args[1]))
					{
<<<<<<< HEAD
						printf("wrong argumenst\n Comand :: >> 2;\"year\";\"author\"\n");
=======
						printf("Wrong arguments\n Command :: >> 2 \"year\" \"author\"\n");
>>>>>>> a182e060a30460d9762bf05915ef336c829f91a7
						break;
					}
					else
					{	/*verificar se o autor existe*/


						/*se existe fazer*/
						int year = catHash(atoi(args[1]));
						int np = yearpublications(catalog[year],args[2]);
						printf("O Autor %s publicou %d vezes no ano %d\n", args[2],np,atoi(args[1]));
							break;
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
<<<<<<< HEAD
							printf("wrong argumenst\n Comand :: >> 4;\"Autor\"\n");
=======
							printf("Wrong arguments\n Command :: >> 4 \"Autor\"\n");
>>>>>>> a182e060a30460d9762bf05915ef336c829f91a7
							break;
						}
						else
						{
							/*ver se autor existe*/
							table_pubsByYear(catalog,args[1],menor_ano,maior_ano);
							break;
						}
				}
		
				case 5:
				{
						/*indice dada uma letra*/
						break;
				}

				case 6:
				{
					/*total de pubs entre dintervalo de anos*/
					break;
				}
				case 7:
				{
					/*det co-auotres*/
					if(narg != 2)
					{
<<<<<<< HEAD
						printf("wrong argumenst\n Comand :: >> 7;\"Autor\"\n");
=======
						printf("Wrong arguments\n Command :: >> 7 \"Autor\"\n");
>>>>>>> a182e060a30460d9762bf05915ef336c829f91a7
							break;
					}
					else
					{
						printCo_autores(catalog,args[1]);
						break;
					}
				}
				
				case 8:
				{ 
					if(narg!=3 || !isInt(args[1]) || !isInt(args[2]))
					{
						printf("wrong argumenst\n Comand :: >> 8;\"year1\";\"year2\" \n");
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
					/*tabela para um ano tipo csv*/
					break;
				}

				case 10:
				{
					/*CSV*/
					break;
				}

				case 11:
				{
					if(narg!=2 || !isInt(args[1]))
					{
						printf("wrong argumenst\n Comand :: >> 11;\"N authors\"\n");
						break;
					}
					else
					{
						Names names  =NULL;
						names = getIndNames(indice,names);
						i=0;
						
						n_authors(catalog,names,10);
						/*lista dos N autores com maior numero de publicaçoes*/
						break;
					}
				}

				case 12:
				{
					/*percentagem de pubs num ano*/
					break;
				}

				case 13:
				{
					/* media dos tamnahos dos nomes dos autores*/
					break;
				}

				default: 
				{		printf("Command number %d does not exist\nChoose a number from Menu\n",op);
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

free(line);
fclose(fl);
free(indice);
free(catalog);

return 0;
}
