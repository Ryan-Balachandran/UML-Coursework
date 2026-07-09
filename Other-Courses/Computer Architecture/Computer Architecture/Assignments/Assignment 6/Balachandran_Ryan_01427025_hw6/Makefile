CC = gcc
CFLAGS = -o -Werror -Wextra -Wall
TARGET = linker

all: link view build dump run

link: linker.o
	$(CC) $(CFLAGS) linker.c -o $(TARGET)

view:
	cat main.asm
	@echo "";
	cat writeint.asm
	@echo "";
	cat readint.asm
	@echo "";
	cat writestr.asm
	@echo "";
	cat addints.asm
	@echo "";
	cat xbsywt.asm
	@echo "";
	cat rbsywt.asm
	@echo "";
	cat sb.asm
	@echo "";
	cat data.asm
	@echo "";

build:
	./masm_mrd -o < main.asm > main.o
	cat main.o
	@echo "";
	./masm_mrd -o < writeint.asm > writeint.o
	cat writeint.o
	@echo "";
	./masm_mrd -o < readint.asm > readint.o
	cat readint.o
	@echo "";
	./masm_mrd -o < writestr.asm > writestr.o
	cat writestr.o
	@echo "";
	./masm_mrd -o < addints.asm > addints.o
	cat addints.o
	@echo "";
	./masm_mrd -o < xbsywt.asm > xbsywt.o
	cat xbsywt.o
	@echo "";
	./masm_mrd -o < rbsywt.asm > rbsywt.o
	cat rbsywt.o
	@echo "";
	./masm_mrd -o < sb.asm > sb.o
	cat sb.o
	@echo "";
	./masm_mrd -o < data.asm > data.o
	cat data.o
	@echo "";

dump: 
	./linker -o main.o writeint.o readint.o writestr.o addints.o xbsywt.o rbsywt.o sb.o data.o > cons_link.o
	cat cons_link.o
	@echo "";

run:
	./linker main.o writeint.o readint.o writestr.o addints.o xbsywt.o rbsywt.o sb.o data.o > cons_link.exe
	cat cons_link.exe
	@echo "";

clean:
	rm -f *.o *.obj *.exe linker
