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
	gcc -o executavel GESTAUTS.c parser.o indAuthors.o

exec:	executavel
	./executavel PUBLICX_FILES/publicx_x4.txt 

all: clear clean exec
