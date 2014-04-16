default: all

clear:
	clear

clean:
	rm -f *.o out.txt GESTAUTS

parser.o: Source/parser.c Headers/parser.h
	gcc -c -ansi Source/parser.c

indAuthors.o: Source/indAuthors.c Headers/indAuthors.h
	gcc -c -ansi Source/indAuthors.c

catalog.o: Source/catalog.c Headers/catalog.h
	gcc -c -ansi Source/catalog.c	

catalogHandler.o: Source/catalogHandler.c Headers/catalogHandler.h catalog.o 
	gcc -c -ansi Source/catalogHandler.c	

indiceHandler.o: Source/indiceHandler.c Headers/indiceHandler.h catalog.o indAuthors.o
	gcc -c -ansi Source/indiceHandler.c

GESTAUTS: GESTAUTS.c parser.o indAuthors.o catalog.o catalogHandler.o indiceHandler.o
	gcc -o GESTAUTS -ansi  GESTAUTS.c catalog.o parser.o indAuthors.o catalogHandler.o indiceHandler.o

exec: GESTAUTS
	./GESTAUTS PUBLICX_FILES/publicx.txt 

all: clear clean exec
