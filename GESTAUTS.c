#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/indAuthors.h"
#include "Headers/parser.h"
#include "Headers/catalog.h"


int main(int argc,char** argv)
{
	if(argc!= 2){
		printf("Wrong arguments!\nSintax: GESTAUTS 'file_path'\n");
	return 1;
   }
   time_t seconds = time(NULL);
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
time_t seconds2 = time(NULL);
printf("inicialização durou :: %ld segundos\n", (seconds2-seconds) );







free(line);
fclose(fl);
free(indice);
free(catalog);

return 0;
}