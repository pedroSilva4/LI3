#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/parser.h"

char* getName(char* string)
{
	
int i =0;
char* aux;
char* aux2 = malloc(1000);
int j = 0;
for(i;(string[i]!= ',');i++)
{
	/*aux[i] = string[i];*/
	
	j = i+1;
	if(string[i+1]==',')
	break;	
}

aux = malloc(j+1);
aux = strncpy(aux,string,j);
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
int k = 0;
	while(string[j]!='\n')
	{
		aux[k] = string[j];
		k++;
		j++;
	}
	
strcpy(string,aux);
/*free(aux);*/

}

int getyear(char* string)
{ 
	int i =  atoi(string);
	free(string);
	return i;
}




void lineParser(char string[],int* nn,int* year,int * nap,char *** nomes )
{
 

char ** parsedNames = malloc(300 * sizeof(char*));

int na = 0;
int ano = 0;
int i  = 0;



while(string[0]!='\n'|| string[0]!='\0')
{
	if(string[0]!= ',' && string[0]!= ' ' && !isdigit(string[0])){
		
		parsedNames[i] =  malloc(50);
		parsedNames[i] = getName(string);
		na++;
		i++;
	
	

	}
	else{
			if(isdigit(string[0])){
				
				ano = getyear(string);
			
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

}
