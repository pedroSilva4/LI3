#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/parser.h"

char* getName(char* string)
{
	
int i =0;
char* aux = malloc(450);
char* aux2 = malloc(1000);
int j = 0;
for(i;(string[i]!= ',');i++)
{
	aux[i] = string[i];
	j = i+1;	
}

int k = 0;
while(string[j] !='\n')
{
	aux2[k] = string[j];
	j++;
	k++;
}

strcpy(string,aux2);
free(aux2);
return aux;

}

void eatComaSpace(char* string)
{ 
	char* aux = malloc(1000);
	int j = 0;
	while(string[j] == ','||string[j]==' ')
	{

		j++;
		
	}
//printf("ok eat meio\n");
int k = 0;
	while(string[j]!='\n')
	{
		aux[k] = string[j];
		k++;
		j++;
	}
	//printf("ok eat saida\n");
strcpy(string,aux);
free(aux);

}

int getyear(char* string)
{ //printf("stringlol : %s\n",string );
	int i =  atoi(string);
free(string);
	return i;
}




void lineParser(char string[],int* nn,int* year,int * nap,char *** nomes )
{
 
//printf("inside\n");
char ** parsedNames = malloc(300 * sizeof(char*));

int na = 0;
int ano = 0;
int i  = 0;



while(string[0]!='\n'|| string[0]!='\0')
{
	if(string[0]!= ',' && string[0]!= ' ' && !isdigit(string[0])){
		
		parsedNames[i] =  malloc(450);
		parsedNames[i] = getName(string);
		na++;
		i++;
	
	

	}
	else{
			if(isdigit(string[0])){
				//printf("entrada do getyear : %s\n",string);
				ano = getyear(string);
			//printf("ano : %d\n",year);
				break;
				}

			else
			{
				
				 eatComaSpace(string);	
				
		
			}
	}	
}

*nn += na;
*nap= na;
*year = ano;
*nomes = parsedNames;
//free(*parsedNames);
}


/*int main(int argc,char **argv)
{
	int entradas = 0;
	int menor_ano = 2015;
	int maior_ano = 0;
	int autores = 0;
	char *filename = argv[1];
	FILE* fl = fopen(filename,"a+");
	int read;
	char * line = NULL;
	size_t len = 0;
	char **nomesautores;
	int ano;

int i;
	while ((read = getline(&line, &len, fl)) != -1) {
//printf("ok\n");
//printf("%s\n",line);
int nap =0;
    lineParser(line,&autores, &ano,&nap,&nomesautores);
    
    if(ano > maior_ano)
    	maior_ano = ano;

    if(ano < menor_ano)
    	menor_ano = ano;
 
    printf("%s\n",nomesautores[0] );
    entradas++;
  //printf("%d\n",entradas );
}
printf("Ficheiro: %s\n", filename);
printf("Publicaçoes: %d\n",entradas );
printf("Numero total de autores: %d\n",autores );
printf("Intervalo de anos: [%d-%d]\n", menor_ano,maior_ano);



fclose(fl);








}
*/

