.cpp.o:
	g++ -c -g $*.cpp

hello: main.o dumb.o
	g++ -o hello main.o dumb.o

main.o: main.cpp dumb.h
dumb.o: dumb.cpp dumb.h

tags:
	etags *.cpp *.h
	ctags *.cpp *.h
