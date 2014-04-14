#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indAuthors.h"
#include "parser.h"
#include "catalog.h"


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
	indice = malloc(28*sizeof(Node));
	for(i;i<28;i++)
		indice[i] = NULL;
	Catalog * catalog;
	catalog = catInit(catalog);

i=0 ;
	while ((read = getline(&line, &len, fl)) != -1) {
	int nap= 0;
	char** nomes;
	lineParser(line,&autores, &ano,&nap,&nomes); 

    if(ano > maior_ano)
    	maior_ano = ano;

    if(ano < menor_ano)
    	menor_ano = ano;
 
catalog = add(catalog,ano,nomes,nap); 

/*while(nap>0)
{
 indice = addToInd(indice ,nomes[nap-1]);
nap--;
}
 */

    //printf("%s\n", nomes[0]);
    entradas++;
 
    free(nomes);
    len= 0;
}
printf("Ficheiro: %s\n", filename);
printf("Publicaçoes: %d\n",entradas );
printf("Numero total de autores: %d\n",autores );
printf("Intervalo de anos: [%d-%d]\n", menor_ano,maior_ano);




/*
i=0;
for(;i<56;i++)
{
	if(catalog[i])
	{
		printf(":::::::ANO %d::::::::\n", i+1960);
		while(catalog[i]){
		printf("%s\n",catalog[i]->author );
		printf("%d\n",catalog[i]->np);
		while(catalog[i]->relations)
		{
			printf("rel :: %s ++ ntimes:: %d\n",catalog[i]->relations->name,catalog[i]->relations->ntimes);
			catalog[i]->relations = catalog[i]->relations->next;
		}
		catalog[i] = catalog[i]->next;
		}
	}
}

*/








//printIndice(indice);
free(line);
fclose(fl);
free(indice);
free(catalog);
time_t seconds2 = time(NULL);
printf("time in seconds :: %ld\n", (seconds2-seconds) );
return 0;
}