default: all

clear:
	clear

clean:
	rm -f *.o executavel 

parser.o: parser.c parser.h
	gcc -c parser.c

indAuthors.o: indAuthors.c indAuthors.h
	gcc -c indAuthors.c

executavel: GESTAUTS.c parser.o indAuthors.o
	gcc -o executavel GESTAUTS.c parser.o indAuthors.o -ll

exec:	executavel
	./executavel PUBLICX_FILES/publicx.txt 

all: clear clean exec
