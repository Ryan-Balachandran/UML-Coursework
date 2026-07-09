all: PS1a

PS1a: LFSR.o test.o
	g++ LFSR.o test.o -lboost_unit_test_framework -o PS1a

LFSR.o: LFSR.cpp LFSR.hpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic LFSR.cpp

test.o: test.cpp
	g++ -c -Wall -Werror -ansi -std=c++11 -pedantic test.cpp

clean:
	\rm *.o *~ PS1a
