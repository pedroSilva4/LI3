#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{
	char* nomes[]={"Ana","Carlos","Manuel"};
	char* nome = "Bruno";
int i = 0;
int j = 0;
char* new[(sizeof(nomes)/sizeof(nomes[0]))+1];
for(i =0 ;nomes[i]!=NULL;i++)
{ 

      if(strcmp(nome,nomes[i]) < 0 && j==0)
      {
      	new[i]=nome;
      	new[i+1] = nomes[i];
      	j=1;
      }
      else 
      {
      	if(j!=0){
      	new[i+1]=nomes[i];
      	}
      	else {new[i]=nomes[i];
      		 new[i+1] = nome;
      		}
      }

}


for(i =0 ;new[i]!=NULL;i++)
{
	printf("%s\n",new[i] );
}

}