all: PSX

PSX: Main.o PTree.o
	g++ Main.o PTree.o -o PSX -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Main.o: Main.cpp PTree.hpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic Main.cpp

pTree.o: PTree.cpp PTree.hpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic PTree.cpp

clean:
	\rm *.o *~ PSX
