CC = gcc
CFLAGS = -o -Werror -Wextra -Wall
TARGET = linker

all: link view build object run

link: linker.o
	$(CC) $(CFLAHS) linker.c -o $(TARGET)
	
view:
	cat lcshift_main.asm
	@echo "";
	@echo "";
	cat lcshift.asm
	@echo "";

build:
	./masm_mrd -o < lcshift_main.asm > lcshift_main.o
	cat lcshift_main.o
	@echo "";
	./masm_mrd -o < lcshift.asm > lcshift.o
	cat lcshift.o
	@echo "";

object:
	./linker -o lcshift_main.o lcshift.o > cons_link.o
	cat cons_link.o
	@echo "";

run:
	./linker lcshift_main.o lcshift.o > cons_link.exe
	cat cons_link.exe
	@echo "";
	./mic1 prom_mrd.dat cons_link.exe 0 1024

clean:
	rm -f *.o *.obj *.exe linker
