.SUFFIXES: .mli .mll .mly .ml .cmo .cmi .cmx
.ml.cmo :
	ocamlc -c $(OFLAGS) $(INCLUDES) $<
.mli.cmi :
	ocamlc -c $(OFLAGS) $(INCLUDES) $<
.ml.cmi :
	ocamlc -c $(OFLAGS) $(INCLUDES) $<
.ml.cmx :
	ocamlopt -c $(OFLAGS) $(INCLUDES) $<
.mll.ml :
	ocamllex $(OLEXFLAGS) $<
.mly.ml :
	ocamlyacc $(OYACCFLAGS) $<
.mly.mli:
	ocamlyacc $(OYACCFLAGS) $<

.ml.o:
	ocamlopt -c -o $@ $(OFLAGS) $(INCLUDES) $<

# The following rule is used to automatically generate a module interface file
# (.mli). It is commented out because it should be used with caution.
# In this project, we should not modify the .mli file!
#.ml.mli:
#	ocamlbuild $<.inferred.mli

OFLAGS=
OLEXFLAGS=
OYACCFLAGS=

EXE=print_pt.exe
OBJ=myParser.o print_pt.o
DEPS=myParser.mli

.PHONY: all clean

# make all:
#	ocamlopt -c -o myParser.o myParser.ml
#	ocamlopt -c -o print_pt.o print_pt.ml
#	ocamlopt -o print_pt myParser.o print_pt.o
all: $(DEPS) $(OBJ)
	ocamlopt -o $(EXE) $(OBJ)

# make clean:
#	rm *.cm* *.o print_pt.exe
clean:
	rm *.cm* $(OBJ) $(EXE)

