all: NBody

NBody: main.o NBody.o
	g++ main.o NBody.o -o NBody -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp NBody.hpp
	g++ -c -Wall -Werror -ansi -std=c++14 -pedantic main.cpp

NBody.o: NBody.cpp NBody.hpp
	g++ -c -Wall -Werror -ansi -std=c++14 -pedantic NBody.cpp

clean:
	\rm *.o *~ NBody
