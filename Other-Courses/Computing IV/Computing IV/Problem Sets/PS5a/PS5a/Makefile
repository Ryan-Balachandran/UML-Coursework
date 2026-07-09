CC = g++
CFLAGS = -c -g -std=c++11 -Wall -ansi -pedantic -Werror 
LFLAGS = -lboost_unit_test_framework -lsfml-window -lsfml-graphics -lsfml-system
OFLAGS = -o

all: GuitarHero

GuitarHero: RingBuffer.o test.o
	$(CC) RingBuffer.o test.o $(OFLAGS) GuitarHero $(LFLAGS)

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) $(CFLAGS) RingBuffer.cpp

test.o: test.cpp RingBuffer.hpp
	$(CC) $(CFLAGS) test.cpp

clean:
	\rm *.o *~ GuitarHero
