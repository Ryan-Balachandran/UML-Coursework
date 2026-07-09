Step 1) Translating the C code into C++ code was easy to do with little complications

Step 2) Extending the language with if and do/check statements was more difficult, comparing the original calculator language with the extended language to see what needed to be added and changed other than the inclusion of if/fi, do/od, and check statements.

Step 3) Implementing the exception-based syntax error recovery took some time to figure out where to put the catch blocks and what to put in the throw statements for the statement, relations and expressions.

Step 4) Not sure I did a good job on coding the Abstract Syntax Tree.

To run the program, these are the steps I did in the terminal:

1) make

2) ./parse < average.cl > output.txt
	- average.cl can be replaced by any other calculator program


Note) I do not know how to add a target test in the makefile to pile sample calculator programs into the parser