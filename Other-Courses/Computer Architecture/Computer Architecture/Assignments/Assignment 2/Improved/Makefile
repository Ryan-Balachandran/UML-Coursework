CC = gcc
CFLAGS = -o -Werror -Wextra -Wall
TARGET = floatingpoint

all: floatingpoint.o
	$(CC) $(CFLAGS) floatingpoint.c -o $(TARGET)
	#./floatingpoint < input.txt > output.txt

clean:
	$(RM) $(TARGET) *.o