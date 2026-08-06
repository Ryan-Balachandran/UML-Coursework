CC = g++
OBJS = RingBuffer.o GuitarString.o GuitarHero.o
CFLAGS = -c -g -std=c++11 -Wall -Werror -ansi -pedantic
LFLAGS = -lboost_unit_test_framework -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

all: GuitarHero

GuitarHero: $(OBJS)
	$(CC) $(OBJS) -o GuitarHero $(LFLAGS)

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) $(CFLAGS) RingBuffer.cpp

GuitarString.o: GuitarString.cpp GuitarString.hpp RingBuffer.hpp
	$(CC) $(CFLAGS) GuitarString.cpp

GuitarHero.o: GuitarHero.cpp GuitarString.hpp RingBuffer.hpp
	$(CC) $(CFLAGS) GuitarHero.cpp

#--------------------TEST FILES--------------------#
GStest.o: GStest.cpp GuitarString.hpp RingBuffer.hpp
	$(CC) $(CFLAGS) GStest.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean:
	\rm *.o *~ GuitarHero

