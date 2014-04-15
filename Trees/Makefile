default: all

clear:
	clear

clean:
	rm -f *.o executavel 

parser.o: parser.c parser.h
	gcc -c parser.c

indAuthors.o: indAuthors.c indAuthors.h
	gcc -c indAuthors.c

catalog.o: catalog.c catalog.h
	gcc -c catalog.c	

executavel: GESTAUTS.c parser.o indAuthors.o catalog.o
	gcc -o executavel GESTAUTS.c catalog.o parser.o indAuthors.o

exec:	executavel
	./executavel PUBLICX_FILES/publicx.txt 

all: clear clean exec
