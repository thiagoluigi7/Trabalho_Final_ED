#   Trabalho de Estrutura de Dado
#   Monte Olimpo
#   Copyright 2018 by Davi Horner
#                     Gabriel Amorim
#                     Thiago Luigi
#   Arquivo Makefile

CPP = g++
CPPFLAGS = -W -Wall -g -ansi -pedantic

OBJ = deusesGregos.o hash.o trabalho.o

trabalho: $(OBJ)
	g++ -W -Wall -g -ansi -pedantic $(OBJ) -o trabalho

trabalho.o: trabalho.cpp
	g++ -W -Wall -g -ansi -pedantic -c trabalho.cpp -o trabalho.o

hash.o: hash.cpp hash.h
	g++ -W -Wall -g -ansi -pedantic -c hash.cpp -o hash.o

deusesGregos.o: deusesGregos.cpp deusesGregos.h
	g++ -W -Wall -g -ansi -pedantic -c deusesGregos.cpp -o deusesGregos.o

all: trabalho

clean:
	rm -rf *.o