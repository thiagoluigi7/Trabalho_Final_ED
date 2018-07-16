trabalho: trabalho.o Métodos.o
	g++ -o trabalho $<

trabalho.o: trabalho.cpp
	g++ -Wall -o trabalho.o -c trabalho.cpp 

Métodos.o: Implementação.cpp Métodos.h 
	g++ -Wall -o Métodos.o -c Implementação.cpp 

clean:
	rm -rf *.o
