How to handle the collection of translate functions
===================================================

Recall the AST type declarations:

type ast_sl = ast_s list
and ast_s =
    | AST_error
    | AST_assign of (string * ast_e)
    | AST_read of string
    | AST_write of ast_e
    | AST_if of (ast_e * ast_sl)
    | AST_do of ast_sl
    | AST_check of ast_e
and ast_e =
    | AST_binop of (string * ast_e * ast_e)
    | AST_id of string
    | AST_num of string;;



Referring to the type definitions above, here is a way to think about the collection of translate functions.

•	translate (ast:ast_sl) : string*string
	Returns the pair (warnings_string, prologue_string ^ (translate_sl sl) ^ epilogue_string) (where ^ is the string concatenation operator).
	
•	translate_sl (ast:ast_sl) : string
	Calls translate_s for each statement node in the statement list ast, and returns a string which is the result of concatenating the individual statement strings returned by each of the calls to translate_s .
	Hint: Do a Google search for “OCaml List.map” for a handy iterator function in the List library package.
	
•	translate_s (stmt:ast_s) : string
	Basically is just a match statement that matches the stmt parameter against the various ast_s node types (e.g., AST_assign), calls the corresponding function (e.g., translate_assign), then returns that function’s return value (a string containing the resulting C code).
	
•	translate_assign, translate_read, etc.
	One function for each of the six types of statements in the ECG. Each of these should return a string containing the translation of the ECG statement into the corresponding C statement.