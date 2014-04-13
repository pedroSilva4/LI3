#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED


typedef struct publicacao
{
	char** autores;
	int ano;
} Publicacao;

struct llpubs
{
	Publicacao pub;
	struct stats* next;
};


typedef llpubs** Stats;



#endif