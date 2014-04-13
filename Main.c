#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* getName(char* string)
{
	
int i =0;
char* aux = malloc(sizeof(string));
char* aux2 = malloc(sizeof(string));
int j = 0;
for(i;(string[i]>='A'&& string[i]<='z') || string[i]==' ';i++)
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

return aux;

}

void eatComaSpace(char* string)
{ 
	char* aux = malloc(sizeof(string));
	int j = 0;
	while(string[j] == ',' || string[j]==' ')
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


}

int getyear(char* string)
{
	int i =  atoi(string);
	string = NULL;
	return i;
}




int main(int argc,char** argv)
{
 char string[] = "coisas, outras coisas, todas tolas, 2010\n";

int i = 0;
char* parsedNames[sizeof(string)];
while(string[0]!='\n'|| string[0]!='\0')
{
	if(string[0] >= 'A' && string[0]<= 'z'){
		
	parsedNames[i] = malloc(sizeof(string));
		parsedNames[i] = getName(string);
	
	printf("%d : %s\n", i, parsedNames[i]);
	i++;
	}
	else{
			if(isdigit(string[0])){
				int in = getyear(string);
				printf("ano : %d\n",in );
				break;
				}

			else
			{
				eatComaSpace(string);	
		
			}
	}	
}

return 0;
}


