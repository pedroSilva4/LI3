#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "indAuthors.h"
#include "parser.h"


int main(int argc,char** argv)
{
	if(argc!= 2){
		printf("Wrong arguments!\nSintax: GESTAUTS 'file_path'\n");
	return 1;
   }
 
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
	Indice* indice =(Indice * ) malloc(28*sizeof(Node));
	int ind = 0;
	while(ind<28)
	{
		indice[ind] = malloc(sizeof(Node));
		indice[ind] = NULL;
		ind++;
	}

char** nomes;
int i = 0;
	while ((read = getline(&line, &len, fl)) != -1) {
	int nap= 0;
	
	lineParser(line,&autores, &ano,&nap,&nomes);
	//printf("ok %d\n", i);
  
  //i++;
// printf("nap-->%d\n",nap);

	indice = addToInd(indice,nomes[0]);
	

nomes = NULL;
i = 0;
  // indice = addToInd(indice,nomes[0]);

    if(ano > maior_ano)
    	maior_ano = ano;

    if(ano < menor_ano)
    	menor_ano = ano;
 
    
    entradas++;
  //printf("%d\n",entradas );
}
printf("Ficheiro: %s\n", filename);
printf("Publicaçoes: %d\n",entradas );
printf("Numero total de autores: %d\n",autores );
printf("Intervalo de anos: [%d-%d]\n", menor_ano,maior_ano);



fclose(fl);


 






return 0;
}