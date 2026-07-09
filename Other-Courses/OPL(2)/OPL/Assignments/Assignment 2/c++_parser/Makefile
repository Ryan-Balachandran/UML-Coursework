# Trivial makefile for the calculator scanner/parser.
# Depends on default (built-in) rules for C++ compilation.

# Note that rule for goal (parse) must be the first one in this file.

parse: parse.o scan.o
	g++ -o parse parse.o scan.o

clean:
	rm *.o parse

test: parse
	./parse < ./input/input.txt > ./output/output.txt
	./parse < ./input/input1.txt > ./output/output1.txt
	./parse < ./input/input2.txt > ./output/output2.txt
	./parse < ./input/input3.txt > ./output/output3.txt
	./parse < ./input/input4.txt > ./output/output4.txt
	./parse < ./input/input5.txt > ./output/output5.txt
	./parse < ./input/input6.txt > ./output/output6.txt
	./parse < ./input/input7.txt > ./output/output7.txt
	./parse < ./input/input8.txt > ./output/output8.txt
	./parse < ./input/input9.txt > ./output/output9.txt

parse.o: scan.h
scan.o: scan.h
