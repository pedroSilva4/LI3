default: all

clear:
	clear

clean:
	rm -f *.o GESTAUTS

parser.o: Source/parser.c Headers/parser.h
	gcc -c Source/parser.c

indAuthors.o: Source/indAuthors.c Headers/indAuthors.h
	gcc -c Source/indAuthors.c

catalog.o: Source/catalog.c Headers/catalog.h
	gcc -c Source/catalog.c	

GESTAUTS: GESTAUTS.c parser.o indAuthors.o catalog.o
	gcc -o GESTAUTS GESTAUTS.c catalog.o parser.o indAuthors.o

exec: GESTAUTS
	./GESTAUTS PUBLICX_FILES/publicx_x6.txt 

all: clear clean exec
