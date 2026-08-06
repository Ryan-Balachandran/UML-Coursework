CC = g++
OFLAGS = -c  -std=c++11 -g
CFLAGS = -std=c++11 -g -O2

all: PAIRWISE

PAIRWISE: Main.o pairwise.o
	$(CC) Main.o pairwise.o $(CFLAGS) $(LFLAGS) -o PAIRWISE

Main.o: Main.cpp
	$(CC) $(OFLAGS) $(LFLAGS) Main.cpp

pairwise.o: pairwise.cpp pairwise.hpp
	$(CC) $(OFLAGS) pairwise.cpp

clean:
	\rm *.o *~ PAIRWISE


