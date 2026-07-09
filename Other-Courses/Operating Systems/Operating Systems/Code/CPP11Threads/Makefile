CC = g++
CFLAGS = -c -g -Og -std=c++14
OBJ = Futures.o
DEPS = 
LIBS = -pthread
EXE = a.out

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)
