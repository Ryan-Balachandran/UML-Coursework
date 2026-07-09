(*******************************************************************
    This file ("translator.ml") provides stub functions for the extra
    code you need to write for this assignment.


    There are two major stub functions in "translator.ml":
    "ast_ize_P" (which transforms a parse tree for a program into
                 an abstract syntax tree[AST]); and
    "translate" (which translates an AST into an equivalent C program).


    You are also being provided with a file called "parser.ml" which
    contains working code to produce a parse tree for a program.
    Everything in the file "parser.ml" is complete and usable as-is.


    The major entry point for the parser provided in "parser.ml" is
    a function called "parse" invoked with two parameters: A parse table,
    and a string containing a calculator language program.


    The file "parser.ml" constructs two example parse tables:
    "cg_parse_table" (for the original calculator language grammar), and
    "ecg_parse_table" (for the extended calculator language grammar).


    Here are two parser examples which will work as-is:

       parse cg_parse_table sum_ave_prog;;
       parse ecg_parse_table primes_prog;;
   		

    "sum_ave_prog" and "primes_prog" are provided at the end of this
    file (as strings). "sum_ave_prog" uses the original calculator
    language grammar, while "primes_prog" uses the extended calculator
    language grammar.


    When complete, your translator code should work when invoked as
    follows:


	print_string
	     (snd
	          (translate
	               (ast_ize_P
	                    (parse ecg_parse_table primes_prog)
	               )
	          )
	     );;

	print_string(snd(translate(ast_ize_P(parse ecg_parse_table primes_prog))));;

    The result of this invocation should be a C program on standard
    output, which can be compiled and run to produce the first N primes
    (where N is a number typed by the user).
********************************************************************)


#use "parser.ml";;


(*******************************************************************
   Declarations and functions to transform a parse tree into an
   abstract syntax tree (AST)
********************************************************************)
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


let rec ast_ize_P (p:parse_tree) : ast_sl =
	match p with
   	| PT_nt ("P", slist) -> ast_ize_SL (hd slist)
    	| _                  -> raise (Failure "malformed parse tree in ast_ize_P")


and ast_ize_SL (sl:parse_tree) : ast_sl =
  	match sl with
    	| PT_nt ("SL", [])         -> []
    	| PT_nt ("SL", head::tail) -> [ast_ize_S head] @ (ast_ize_SL (hd tail))
    	| _                        -> raise (Failure "malformed parse tree in ast_ize_SL")


and ast_ize_S (s:parse_tree) : ast_s =
  	match s with
    	| PT_nt ("S", [PT_id lhs; PT_term ":="; expr])        -> AST_assign (lhs, (ast_ize_expr expr))
    	| PT_nt ("S", [PT_term "read"; PT_id id])             -> AST_read (id)
	| PT_nt ("S", [PT_term "write"; expr])                -> AST_write (ast_ize_expr expr)
	| PT_nt ("S", [PT_term "if"; expr; sl; PT_term "fi"]) -> AST_if(ast_ize_expr expr, ast_ize_SL sl)
	| PT_nt ("S", [PT_term "do"; sl; PT_term "od"])       -> AST_do (ast_ize_SL sl)
	| PT_nt ("S", [PT_term "check"; expr])                -> AST_check (ast_ize_expr expr)
    	| _  						      -> raise (Failure "malformed parse tree in ast_ize_S")


and ast_ize_expr (e:parse_tree) : ast_e =
	(*** e is an R, E, T, or F parse tree node ***)
	match e with
	| PT_nt ("R", head::rest)                       -> ast_ize_reln_tail (ast_ize_expr head) (hd rest)
	| PT_nt ("E", head::rest)                       -> ast_ize_expr_tail (ast_ize_expr head) (hd rest)
	| PT_nt ("T", head::rest) 		        -> ast_ize_expr_tail (ast_ize_expr head) (hd rest)
	| PT_nt ("F", [PT_num (num)])                   -> AST_num (num)
	| PT_nt ("F", [PT_id (id)])		        -> AST_id (id)
	| PT_nt ("F", [PT_term "("; expr; PT_term ")"]) -> ast_ize_expr (expr)
	| _                       -> raise (Failure "malformed parse tree in ast_ize_expr")


and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
	(*** lhs is an inherited attribute. tail is an ET parse tree node ***)
	match tail with
	| PT_nt ("ET", []) -> lhs	(*** ET -> epsilon ***)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term "=="]); rhs]) -> AST_binop ("==", lhs, ast_ize_expr rhs)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term "<"]); rhs])  -> AST_binop ("<", lhs, ast_ize_expr rhs)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term ">"]); rhs])  -> AST_binop (">", lhs, ast_ize_expr rhs)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term "<="]); rhs]) -> AST_binop ("<=", lhs, ast_ize_expr rhs)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term ">="]); rhs]) -> AST_binop (">=", lhs, ast_ize_expr rhs)
	| PT_nt ("ET", [PT_nt ("ro", [PT_term "<>"]); rhs]) -> AST_binop ("<>", lhs, ast_ize_expr rhs)
	| _ 						    -> raise (Failure "malformed parse tree in ast_ize_reln_tail")


and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
	(*** lhs is an inherited attribute. tail is a TT or FT parse tree node ***)
	match tail with
	| PT_nt ("TT", []) -> lhs	(*** TT -> epsilon ***)
	| PT_nt ("FT", []) -> lhs	(*** FT -> epsilon ***)
	| PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; term_tail])     -> ast_ize_expr_tail (AST_binop (ao, lhs, (ast_ize_expr term))) term_tail	(*** TT -> ao T TT ***)
	| PT_nt ("FT", [PT_nt ("mo", [PT_term mo]); factor; factor_tail]) -> ast_ize_expr_tail (AST_binop (mo, lhs, (ast_ize_expr factor))) factor_tail	(*** FT -> mo F FT ***)	
	| _                -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;










(*******************************************************************
   Functions to translate an AST into C
********************************************************************)

(************************************************************************
   The code below is (obviously) a bare stub. The intent is that when
   you run translate on a full, correct AST, you'll get back code for an
   equivalent C program. If there are any variables that are written in
   the program but never read, you'll also get a warning message
   indicating their names and the lines on which the writes occur. Your
   C program should contain code to check for dynamic semantic errors
*************************************************************************)

(*******************************************************************
   Remove the duplicates in list using fold_left
   The results are in reversed order, but 0(1) space
********************************************************************)
let cons_uniq xs x = if List.mem x xs then xs else x::xs
let remove_duplicates xs = List.fold_left cons_uniq [] xs 


let code_preface = 
"
	#include <stdio.h>
	#include <stdlib.h>

	int getint()
	{
		int n;
		char buf[100];
		
		fgets(buf, sizeof(buf), stdin);

		if (sscanf(buf, \"%d\", &n) != 1)
		{
			if (buf[0] == '\\n')
			{
				printf(\"Error: No Input.\");
			}
			else
			{
				printf(\"Error: Input is not an integer.\");
				exit(0);
			}
		}
		
		return n;
	}

	void putint(int n)
	{
    		// prints an integer and a linefeed to standard output.
		printf(\"%d\\n\", n);
	}

	int zero_breaker(int n)
	{
		if (n == 0)
		{
			printf(\"Error: Divide by 0.\");
			exit(0);
		}
		
		return n;
	}

	int main (void)
	{
    		/* EVERYTHING ABOVE THIS LINE IS THE PROGRAM PROLOGUE */
"


(*******************************************************************
   Collect all assigned variable ( from AST_assign and AST_read)
   And return the collected id list
********************************************************************)
let rec translate (ast:ast_sl) : string * string =	
	let rec traverse_assigned_variables (ast:ast_sl) : string list =
		match ast with
		| []   -> []
		| h::t ->
			match h with
			| AST_assign (id, expr) -> id::traverse_assigned_variables t
			| AST_read (id)		-> id::traverse_assigned_variables t
			| AST_do (sl)		-> traverse_assigned_variables sl @ traverse_assigned_variables t
			| AST_if (expr, sl)	-> traverse_assigned_variables sl @ traverse_assigned_variables t
			| AST_write (expr)
			| AST_check (expr)	-> traverse_assigned_variables t
			| AST_error		-> raise (Failure "traverse_variables error") 
	in

	(************************************************************************
	   Collect all used variables (in expr), no matter it is assigned or not
	*************************************************************************)

	(*****************************************************************************
      	   expr_vars collects all the variables in expr 
      	      if it matches id, then return [id] as a list
      	      if it matches num, then return [] because we only need variables
      	      if it matches binop, then recursively call it on both sides of the op
	******************************************************************************)
	let rec traverse_used_variables (ast:ast_sl) : string list =
		let rec expr_vars (expr:ast_e) : string list = 
			match expr with
			| AST_id (id) -> [id]
			| AST_num (n) -> []
			| AST_binop (op, lhs, rhs) -> expr_vars lhs @ expr_vars rhs
		in

		match ast with
		| []   -> []
		| h::t ->
			match h with
			| AST_assign (id, expr) -> expr_vars expr @ traverse_used_variables t
			| AST_read (id)		-> traverse_used_variables t
			| AST_do (sl)		-> traverse_used_variables sl @ traverse_used_variables t
			| AST_if (expr, sl)	-> expr_vars expr @ traverse_used_variables sl @ traverse_used_variables t
			| AST_write (expr)
			| AST_check (expr)	-> expr_vars expr @ traverse_used_variables t
			| AST_error 		-> raise (Failure "traverse_variables error")
	in

	(****************************************
	   Concatenate all variable declarations
	*****************************************)
	let rec variables_string = function
		| []   -> ""
		| h::t -> "int " ^ h ^ ";\n" ^ variables_string t
	in

	let var_list_assigned = remove_duplicates(traverse_assigned_variables ast) in
	let var_list_used = remove_duplicates(traverse_used_variables ast) in

	(*******************************************
	   This is for Error: variable not assigned
	********************************************)
	let assign_error used assigned =
		let not_assigned = List.filter (fun x -> not (List.mem x assigned)) used in
		let rec n_assign l =
			match l with
			| []   -> ""
			| h::t -> "not assigned var: " ^ h ^ "\\n" ^ n_assign t
		in
		n_assign not_assigned
	in

	(***********************************************
	   This is for Warning: assigned but never used
	************************************************)
	let unused_warning used assigned = 
		let not_used = List.filter (fun x -> not (List.mem x used)) assigned in
		let rec n_use l =
			match l with
			| []   -> ""
			| h::t -> "not used var: " ^ h ^ "\n" ^ n_use t
		in
		n_use not_used
	in

	(***************************************************************
	   Always print warning; only raise error when there exists one
	****************************************************************)
	let error_msg = assign_error var_list_used var_list_assigned in
	let print_error = if error_msg = "" then "false" else "true" in
	let warning_msg = unused_warning var_list_used var_list_assigned in
		(warning_msg, code_preface ^ "if (" ^ print_error ^ ") {\n    printf(\"" ^ error_msg ^ "\");\n    exit(0);\n}\n"
  		^ variables_string var_list_assigned ^ translate_sl ast ^ "return 0;\n}")


and translate_sl (ast:ast_sl) : string =
	match ast with
	| []   -> ""
	| h::t -> translate_s h ^ translate_sl t


and translate_s (s:ast_s) : string =
	match s with
	| AST_assign (id, expr) -> translate_assign id expr
	| AST_read (id)         -> translate_read id
	| AST_write (expr)      -> translate_write expr
	| AST_if (expr, sl)     -> translate_if expr sl
	| AST_do (sl)           -> translate_do sl
	| AST_check (rel)       -> translate_check rel
	| AST_error             -> raise (Failure "translate_s error")


and translate_assign (id:string) (expr:ast_e) : string =
	id ^ " = " ^ (translate_expr expr) ^ ";\n"


and translate_read (id:string) : string =
	id ^ " = getint();\n"		(*** maybe we can pass lineno to getting function ***)


and translate_write (expr:ast_e) : string =
	"putint(" ^ translate_expr (expr) ^ ");\n"


and translate_if (expr:ast_e) (sl:ast_sl) : string =
	"if (" ^ translate_expr (expr) ^ ") {\n" ^ translate_sl (sl) ^ "}\n"


and translate_do (ast:ast_sl) : string =
	"while(1) {\n" ^ translate_sl (ast) ^ "}\n"


and translate_check (expr:ast_e) : string =
	"if (!" ^ translate_expr (expr) ^ ") break;\n"


(*****************************************************************************************
   Wrap the divisor with zero_breaker, because "if" conditions are hard to implement here
******************************************************************************************)
and translate_expr (expr:ast_e) : string =
	match expr with
	| AST_num (n) 		   -> n
	| AST_id (id) 		   -> id
	| AST_binop (op, lhs, rhs) -> if op = "/" then "(" ^ translate_expr (lhs) ^ op ^ "zero_breaker (" ^ translate_expr (rhs) ^ "))"
				      else "(" ^ translate_expr (lhs) ^ op ^ translate_expr (rhs) ^ ")"










(*******************************************************************
   Interpret the program using AST directly
********************************************************************)
type memory = (bool * string * int) list

type status = Good | Bad | Done	
(*******************************************
	Good: continue
	Bad:  runtime error (stop)
	Done: finish (use in check and do)
********************************************)

type value = Value of int | Error 

(*******************************************************************
   Interpret with an AST tree and an input string.
   The value is delimited by using space to create a string list
   to return output string 
********************************************************************)
let rec interpret (ast:ast_sl) (stdin:string) : string =

	(**********************************************************************************
	let print_var_list mem_list =
		print_string "--- variable lists start ---\n";
		let rec aux m_list =
			match m_list with
			| [] -> ()
			| (bo, id, value) :: t -> if (bo = true) then print_string ("true ")
							else print_string ("false ");
							print_string (id); print_string (" ");
							print_int (value); print_string ("\n");
							aux t
			in aux mem_list;
				print_string "--- variable lists end ---\n"; in
	***********************************************************************************)


	let convert_stdin str =
    		split (regexp " ") str in

  	let join_strlist lst =
    		let rec aux = function
      			| []   -> ""
      			| h::t -> h ^ "\n" ^ aux t
    		in aux (rev lst) in

  	let (_, mem, _, outp) =
    		interpret_sl ast [] (convert_stdin stdin) [] in

  (*** 		print_var_list (rev mem); ***)
  		join_strlist outp


and interpret_sl (sl:ast_sl) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	match sl with										  (*** input         output ***)
	| [] -> (Good, mem, input, output)
	| h::t -> let (stat, n_mem, n_input, n_output) = interpret_s h mem input output in
		match stat with
		| Good -> interpret_sl t n_mem n_input n_output
		| Done -> (Done, mem, input, output)
		| _    -> (Bad, mem, input, output)


and interpret_s (s:ast_s) (mem:memory) (inp:string list) (outp:string list) : status * memory * string list * string list =
	match s with
  	| AST_assign(id, expr)  -> interpret_assign id expr mem inp outp
  	| AST_read(id)          -> interpret_read id mem inp outp
  	| AST_write(expr)       -> interpret_write expr mem inp outp
  	| AST_if(expr, sl)      -> interpret_if expr sl mem inp outp
  	| AST_do(sl)            -> interpret_do sl mem inp outp
  	| AST_check(expr)       -> interpret_check expr mem inp outp
  	| _                     -> raise (Failure "interpret_s error")


and interpret_assign (id:string) (expr:ast_e) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
(*******************************************************************
   Drop the existed id from memory list, programmer should add back
   the updated mem if using this function
********************************************************************)
	let drop_target_from_mem (target:string) : memory =
		let rec aux target mem_list =
			match mem_list with
			| [] 		       -> []
			| ((_, id, _) as h)::t -> if id = target then aux target t
						  else h::(aux target t)
			in aux target mem
		in
		let (result, _) = interpret_expr expr mem in
		let new_mem = drop_target_from_mem id in
			match result with
			| Value(r) -> (Good, (false, id, r)::new_mem, input, output)
			| Error    -> (Bad, mem, input, output)


(*******************************************************************
   Add a (id, value) pair into memory if succeed
********************************************************************)
and interpret_read (id:string) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	match input with
	| []   ->
		print_string "no input in read";
		(Bad, mem, input, output)
	| h::t ->
		(*** catch non-numeric and return the right status ***)
		try let a = int_of_string h in
			(Good, (false, id, a) :: mem, t, output)
		with Failure _ ->
			print_string "non-numeric input\n";
			(Bad, mem, t, output)


and interpret_write (expr:ast_e) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	let (ret, new_mem) = interpret_expr expr mem in
		match ret with
		| Value (x) -> (Good, new_mem, input, (string_of_int x)::output)
		| Error     -> (Bad, new_mem, input, output)


and interpret_if (expr:ast_e) (sl:ast_sl) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	let (ret, new_mem) = interpret_expr expr mem in
		match ret with
		| Value (0) -> (Good, new_mem, input, output)
		| Error     -> (Bad, new_mem, input, output)
		| _         -> interpret_sl sl new_mem input output


and interpret_do (sl:ast_sl) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	let (n_status, n_mem, n_input, n_output) = interpret_sl sl mem input output in
		match n_status with
		| Good -> interpret_do sl n_mem n_input n_output
		| Done -> (Good, mem ,input, output)
		| Bad  -> (Bad, mem, input, output)


and interpret_check (expr:ast_e) (mem:memory) (input:string list) (output:string list) : status * memory * string list * string list =
	let (ret, new_mem) = interpret_expr expr mem in
		match ret with
		| Value (0) -> (Done, new_mem, input, output)
		| Error     -> (Bad, new_mem, input, output)
		| _         -> (Good, new_mem, input, output)


and interpret_expr (expr:ast_e) (mem:memory) : value * memory =
	(*******************************************************************
   	   return the value of id from the memory which is an integer
	********************************************************************)
	let rec find_val (id:string) (mem_list:memory) : int =
		match mem_list with
		| [] 			-> raise (Failure "use of an uninitialized variable")
		| (_, target, value)::t -> if id = target then value else find_val id t in
	let rec update_mem (id:string) (mem_list:memory) : memory =	(*** update the used id ***)
		match mem_list with
		| [] -> []
		| ((bo, target, value) as h)::t -> if id = target && bo = false then (true, target, value)::(update_mem id t)
						   else h::(update_mem id t) in
	match expr with
	| AST_num(n) -> (Value (int_of_string n), mem)
	| AST_id(id) -> (Value (find_val id mem), (update_mem id mem))
	| AST_binop(op, lhs, rhs) ->	(*** first match left and then right ***)
		match interpret_expr lhs mem with
		| (Error, _)        -> (Error, mem)
		| (Value (left), _) ->
			match interpret_expr rhs mem with
			| (Error, _)         -> (Error, mem)
			| (Value (right), _) ->
				match op with
				| "+" -> (Value (left + right), mem)
				| "-" -> (Value (left - right), mem)
				| "*" -> (Value (left * right), mem)
				| "/" -> if right = 0 then 
						begin
							print_string ("divide by zero\n"); (Error, mem)
						end
					 else (Value (left / right), mem)
				| ">"  -> if left >  right then (Value (1), mem) else (Value (0), mem)
				| "<"  -> if left <  right then (Value (1), mem) else (Value (0), mem)
        			| ">=" -> if left >= right then (Value (1), mem) else (Value (0), mem)
        			| "<=" -> if left <= right then (Value (1), mem) else (Value (0), mem)
        			| "==" -> if left =  right then (Value (1), mem) else (Value (0), mem)
        			| "<>" -> if left <> right then (Value (1), mem) else (Value (0), mem)
				| _    -> raise (Failure "interpret_expr: no such operator")










(*******************************************************************
   Sample programs in the calculator language
********************************************************************)

let sum_ave_prog = "
	read a
	read b
	sum := a + b
	write sum
	write sum / 2";;
	 
let primes_prog = "
	read n
	cp := 2
	do check n > 0
		found := 0
		cf1 := 2
		cf1s := cf1 * cf1
		do check cf1s <= cp
			cf2 := 2
			pr := cf1 * cf2
			do check pr <= cp
				if pr == cp
					found := 1
				fi
			cf2 := cf2 + 1
			pr := cf1 * cf2
		od
		cf1 := cf1 + 1
		cf1s := cf1 * cf1
	od
	if found == 0
		write cp
		n := n - 1
	fi
	cp := cp + 1
  od";;

let comp_f_prog = "
	sum := 1 + (2 * 3)
	write sum
	sum := sum - 1
	write sum";;

let read_write_prog = "
	read a
	read b
	s := 1 + 2
	write a + b + s";;

let do_check_prog = "
	read a
	do check a > 0
		a := a - 1
		write a
	od";;

let division_by_zero_prog = "
	a := 1
	b := 0
	c := a / b";;


(*******************************************************************
   TEST CASES

let translator() =
	let t1 = ast_ize_P(parse ecg_parse_table sum_ave_prog) in
		let (warning, c_prog) = translate t1 in
			print_string (warning ^ c_prog);

	let t3 = ast_ize_P(parse ecg_parse_table comp_f_prog) in
		print_string (snd (translate t3));

	let t4 = ast_ize_P(parse ecg_parse_table read_write_prog) in
		print_string (snd (translate t4));

	let (warning, c_prog) = translate t1 in
		print_string (warning );


let interpreter () =
	let t1 = ast_ize_P (parse ecg_parse_table do_check_prog) in
		print_string (interpret t1 "10");

	let t2 = ast_ize_P(parse ecg_parse_table primes_prog) in
		print_string (interpret t2 "15");

	let t3 = ast_ize_P(parse ecg_parse_table divide_by_zero_prog) in
		print_string (interpret t3 "10");

	let t4 = ast_ize_P(parse ecg_parse_table comp_f_prog) in
		print_string (interpret t4 "1");;
********************************************************************)

