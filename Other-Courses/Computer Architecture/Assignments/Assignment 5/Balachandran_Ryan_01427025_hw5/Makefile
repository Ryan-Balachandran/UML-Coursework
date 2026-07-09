all: build test

build: 
	./masm_mrd < IO_adder.asm > IO_adder.obj

test:
	./mic1 prom_mrd.dat IO_adder.obj 0 1024

clean:
	rm -f *.obj