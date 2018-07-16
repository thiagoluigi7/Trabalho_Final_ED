CPP = g++
CPPFLAGS = -Wall -g

OBJ = deusesGregos.o hash.o trabalho.o

trabalho: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o trabalho

trabalho.o: trabalho.cpp
	$(CPP) $(CPPFLAGS) -c trabalho.cpp -o trabalho.o

hash.o: hash.cpp hash.h
	$(CPP) $(CPPFLAGS) -c hash.cpp -o hash.o 

deusesGregos.o: deusesGregos.cpp deusesGregos.h
	$(CPP) $(CPPFLAGS) -c deusesGregos.cpp -o deusesGregos.o

all: trabalho

clean:
	rm -rf *.o