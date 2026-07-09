CC = g++
CFLAGS = -c -g -Wall -Werror -ansi -pedantic -std=c++11
OBJ = main.o 
DEPS = 
LIBS = -lboost_regex -lboost_date_time
EXE = PS7

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(EXE) *~
