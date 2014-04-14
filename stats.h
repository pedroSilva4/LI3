#ifndef _PARSER_
#define _PARSER_

typedef struct stats
{
	char ** nomes;
	int * nap;
	int * year;
	struct stats *next;

}*Stats, Node;

#endif
