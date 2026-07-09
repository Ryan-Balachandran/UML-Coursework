CC = g++
OFLAGS = -c -Wall -ansi -pedantic -Werror -std=c++11 -g
CFLAGS = -Wall -ansi -pedantic -Werror -std=c++11 -g -O2
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system

all: ED

ED: Main.o ED.o
	$(CC) Main.o ED.o $(CFLAGS) $(LFLAGS) -o ED

Main.o: Main.cpp
	$(CC) $(OFLAGS) $(LFLAGS) Main.cpp

ED.o: ED.cpp ED.hpp
	$(CC) $(OFLAGS) ED.cpp

clean:
	\rm *.o *~ ED


