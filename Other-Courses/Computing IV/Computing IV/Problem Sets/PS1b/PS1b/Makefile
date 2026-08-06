all: PhotoMagic

PhotoMagic: LFSR.o PhotoMagic.o
	g++ LFSR.o PhotoMagic.o -o PhotoMagic -lsfml-graphics -lsfml-window -lsfml-system

LFSR.o: LFSR.cpp LFSR.hpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic LFSR.cpp

PhotoMagic.o: PhotoMagic.cpp LFSR.hpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic PhotoMagic.cpp

clean:
	\rm *.o *~ PhotoMagic
