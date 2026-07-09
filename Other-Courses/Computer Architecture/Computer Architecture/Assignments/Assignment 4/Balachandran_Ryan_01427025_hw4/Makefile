all: masm_nr prom build

masm_nr: mic1symasm.o lex.yy.o
	gcc -o masm_nr mic1symasm.o lex.yy.o

mic1symasm.o: mic1symasm.c
	gcc -c -g mic1symasm.c

lex.yy.o: lex.yy.c
	gcc -c -g lex.yy.c

lex.yy.c: mic1symasm.ll
	flex mic1symasm.ll

prom: microcode.mc
	./mcc microcode.mc > prom.dat

build:
	./masm_nr -o < div_test.asm > div.obj
	./masm_nr -o < mult_test.asm > mult.obj
	./masm_nr -o < rshift_test.asm > rshift.obj

div:
	./mic1 prom.dat div.obj 0 1024

mult:
	./mic1 prom.dat mult.obj 0 1024

rshift:
	./mic1 prom.dat rshift.obj 0 1024

clean:
	rm -f *.o *.obj lex.yy.c lex.yy.o masm_nr prom.dat mic1symasm.o
