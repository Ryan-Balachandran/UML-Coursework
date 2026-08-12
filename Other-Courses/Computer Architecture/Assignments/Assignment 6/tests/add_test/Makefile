CC = gcc
CFLAGS = -o -Werror -Wextra -Wall
TARGET = linker

all: link view build object run

link: linker.o
	$(CC) $(CFLAHS) linker.c -o $(TARGET)
	
view:
	cat main1.asm
	@echo "";
	@echo "";
	cat myadd.asm
	@echo "";

build:
	./masm_mrd -o < main1.asm > main1.o
	cat main1.o
	@echo "";
	./masm_mrd -o < myadd.asm > myadd.o
	cat myadd.o
	@echo "";

object:
	./linker -o main1.o myadd.o > cons_link.o
	cat cons_link.o
	@echo "";

run:
	./linker  main1.o myadd.o > cons_link.exe
	cat cons_link.exe
	@echo "";
	./mic1 prom_mrd.dat cons_link.exe 0 1024

clean:
	rm -f *.o *.obj *.exe linker
