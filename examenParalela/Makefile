CXX = mpic++
CXXFLAGS = -g3 -Wall

LIBS=-lm

Funciones.o:	clean	Funciones.cpp	Funciones.h
	$(CXX) $(CXXFLAGS)  -c	Funciones.cpp
	
all: Funciones.o
	$(CXX) $(CXXFLAGS) -o programita main.cpp Funciones.o 

clean:
	rm -fr *.o a.out programita

.DEFAULT_GOAL := all

