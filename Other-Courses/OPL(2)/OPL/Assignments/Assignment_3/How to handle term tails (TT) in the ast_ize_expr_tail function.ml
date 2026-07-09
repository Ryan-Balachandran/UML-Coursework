How to handle term tails (TT) in the ast_ize_expr_tail function
===============================================================

Recall that the TT parse tree node (non-epsilon case) is the result of the production:

	TT -> ao T TT
	
Note the recursive TT on the right hand side of the production,
which supports simple expressions such as "a+b" as well as arbitrarily long chains
of operations.

For context, here's the part of the ECG grammar that applies to terms 
(we'll ignore factors for this discussion):

E -> T TT
T -> F FT
TT -> ao T TT | epsilon

Here's an example of a string that would be recognized by this grammar:

a+b+c+d

We'll use parens to indicate how the left-most term a+b becomes the lhs for the next term
(a+b)+c, etc.:

(a+b)+c+d
((a+b)+c)+d
(((a+b)+c)+d)

Now let's derive the pattern you need to match for the non-epsilon production.
For example, here's the OCaml representation of the parse tree for the expression "a + b"
(from the sum_ave_prog):

(* parse tree for: a + b *)
PT_nt
("E", (* E -> T TT *)
  [PT_nt ("T", [PT_nt ("F", [PT_id "a"]); PT_nt ("FT", [])]); (* T -> F FT *)
   PT_nt ("TT", (* TT -> ao T TT *)
          [PT_nt ("ao", [PT_term "+"]); (* this is the addop component *)
           PT_nt ("T", [PT_nt ("F", [PT_id "b"]); PT_nt ("FT", [])]); (* this is the T component *)
           PT_nt ("TT", []) (* this is the TT component – in this case, TT -> epsilon *)
          ]
         )
  ])]);

Here’s a pattern that we can use to match that the TT parse tree node in the structure above,
and extract the various components (i.e., ao T TT):
 
	PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; term_tail])
 
If we define the name tt to be the parse tree node structure below,
we can execute the following pattern match in OCaml:
 
	let PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; term_tail]) = tt;;
 
to which OCaml responds (ignoring warning messages about incomplete matching!):
 
	val ao : string = "+"
	val term : parse_tree = PT_nt ("T", [PT_nt ("F", [PT_num "1"]); PT_nt ("FT", [])])
	val term_tail : parse_tree = PT_nt ("TT", [])

In order to handle the recursion in the production TT -> ao T TT,
our function ast_ize_expr_tail could call itself recursively when needed.
The recursion terminates when the right-hand TT is empty (i.e., TT -> epsilon).
It works similarly to recursive descent in our A2 parser.

Now let's see how the return value associated with the above pattern can be executed.

In an imperative language such as C, typically we might execute a set of sequential steps,
such as the following:

	i = x(h);
	j = y(i);
	k = z(j);

The more natural way to accomplish the same thing in a functional language such as OCaml
would be to nest the function calls:

	let k = z( y( x(h) ) );

Here are the steps (x) through (z) for evaluating a non-epsilon TT:

	x.	First, evaluate the term as an expression:
	
			let rhs = ast_ize_expr term
			
	y.	Next, combine the result (acting as the right-hand side of a binop),
		together with the original lhs and the addop:
		
			let lhs2 = AST_binop (ao, lhs, rhs)
			
	z.	Finally, use the resulting AST_binop node as the lhs of the next operation
		in the expression, together with the term_tail,
		via a recursive call to ast_ize_expr_tail:
		
			ast_ize_expr_tail lhs2 term_tail

If we combine steps (x) through (z) into a single set of nested function calls,
we get the following:

	ast_ize_expr_tail (AST_binop (ao, lhs, (ast_ize_expr term))) termtail

Now we substitute the pattern (see line 45 above) and this return value into our definition
of ast_ize_expr_tail:

[...]
and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs is an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
  | PT_nt ("TT", []) -> lhs  (* TT -> epsilon *)
  | PT_nt ("TT", [PT_nt ("ao", [PT_term ao]); term; term_tail]) (* TT -> ao T TT *)
	-> ast_ize_expr_tail (AST_binop (ao, lhs, (ast_ize_expr term))) termtail
  | PT_nt ("FT", []) -> lhs  (* FT -> epsilon *)
  | (* FT -> mo F FT *)
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;