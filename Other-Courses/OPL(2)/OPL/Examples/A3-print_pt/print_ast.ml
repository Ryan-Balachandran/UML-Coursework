(* Example of building and "walking" (traversing) an AST *)
(* To compile:                                           *)
(* 		ocamlopt -o print_ast print_ast.ml               *)

open List;; (* for append *)

(* AST types copied from translator.ml *)

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


let rec print_ast_sl sl =
    print_string ("\nAST_sl [\n  " ^ (stringify_ast_sl sl))
and stringify_ast_sl sl =
  match sl with
  | [] -> "]"
  | head::[] -> stringify_ast_s head ^ "\n]\n"
  | head::rest -> stringify_ast_s head
                  ^ ";\n  " ^ stringify_ast_sl rest
and stringify_ast_s s =
  match s with
  | AST_error -> "AST_error"
  | AST_assign (lhs, rhs) -> "AST_assign(\"" ^ lhs ^ "\", "
                             ^ stringify_ast_e rhs ^ ")"
  | AST_read id -> "AST_read(\"" ^ id ^ "\")"
  | AST_write expr -> "AST_write(" ^ stringify_ast_e expr ^ ")"
  | AST_if (expr, sl) -> "AST_if(" ^ stringify_ast_e expr ^ ", "
                         ^ stringify_ast_sl sl ^ ")"
  | AST_do sl -> "AST_do(" ^ stringify_ast_sl sl ^ ")"
  | AST_check expr -> "AST_check(" ^ stringify_ast_e expr ^ ")"
and stringify_ast_e expr =
  match expr with
  | AST_binop (op, lhs, rhs) -> "AST_binop(\"" ^ op ^ "\", "
                                ^ stringify_ast_e lhs ^ ", "
                                ^ stringify_ast_e rhs ^ ")"
  | AST_id id -> "AST_id \"" ^ id ^ "\""
  | AST_num num -> "AST_num \"" ^ num ^ "\"";;


(* Build a sample AST for the sum_ave_prog    *)
(* (not in a particularly functional fashion) *)

let slist = [];;

(* read a *)
let stmt1 = AST_read("a");;
let slist = append slist [stmt1];;

(* read b *)
let stmt2 = AST_read("b");;
let slist = append slist [stmt2];;

(* sum := a + b *)
let expr = AST_binop("+", AST_id("a"), AST_id("b"));;
let stmt3 = AST_assign("sum", expr);;
let slist = append slist [stmt3];;

(* write sum *)
let expr = AST_id("sum");;
let stmt4 = AST_write(expr);;
let slist = append slist [stmt4];;

(* write sum/2 *)
let expr = AST_binop("/", AST_id("sum"), AST_num("2"));;
let stmt5 = AST_write(expr);;
let slist = append slist [stmt5];;


(* Print the AST for sum_ave_prog *)

(* print_ast_sl slist;; *) 
