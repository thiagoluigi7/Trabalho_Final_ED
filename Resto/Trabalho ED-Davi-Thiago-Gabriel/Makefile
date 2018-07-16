trabalho: trabalho.o hash.o deusesGregos.o
	g++ -o trabalho $<

trabalho.o: trabalho.cpp
	g++ -Wall -o trabalho.o -c trabalho.cpp 

hash.o: hash.cpp hash.h 
	g++ -Wall -o hash.o -c hash.cpp 

deusesGregos.o: deusesGregos.cpp deusesGregos.h
	g++ -Wall -o deusesGregos.o -c deusesGregos.cpp

clean:
	rm -rf *.o