(* sandbox.ml - T. Wilkes, 2020                                                     *)
(*                                                                                  *)
(* The code in this file provides a "sandbox" environment for developing            *)
(* your AST functions in a step-by-step manner.                                     *)
(* This file is self-contained, i.e., you won't need to use any other files         *)
(* while experimenting here.                                                        *)
(* When you get a function working, copy-and-paste it into your translator.ml file. *)

open List;;

(* Parse tree type from parser.ml *)
type parse_tree =
    | PT_error
    | PT_id of string
    | PT_num of string
    | PT_term of string
    | PT_nt of (string * parse_tree list);;

(* AST types from translator.ml *)
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

	
(* Some sample functions demonstrating parse tree pattern matching, *)
(* and building AST nodes                                           *)

let rec ast_ize_P (p:parse_tree) : ast_sl =
  match p with
  | PT_nt ("P", slist) -> ast_ize_SL (hd slist)
  | _ -> raise (Failure "malformed parse tree in ast_ize_P")

and ast_ize_SL (sl:parse_tree) : ast_sl =
  match sl with
    | PT_nt ("SL", []) -> []
	| PT_nt ("SL", head::tail) -> [ast_ize_S head] @ (ast_ize_SL (hd tail))
    | _ -> raise (Failure "malformed parse tree in ast_ize_SL")


and ast_ize_S (s:parse_tree) : ast_s =
  match s with
    | PT_nt ("S", [PT_id lhs; PT_term ":="; expr])
      -> AST_assign (lhs, (ast_ize_expr expr))
	| PT_nt ("S", [PT_term "read"; PT_id id])
	  -> AST_read (id)
(*
your code here ...
*)
    | _ -> raise (Failure "malformed parse tree in ast_ize_S")

and ast_ize_expr (e:parse_tree) : ast_e =
  (* e is an R, E, T, or F parse tree node *)
  match e with
  | PT_nt ("R", head::rest) -> ast_ize_reln_tail (ast_ize_expr head) (hd rest)
  | PT_nt ("E", head::rest) -> (* what to do here? *)
  | PT_nt ("T", head::rest) -> (* what to do here? *)
  | PT_nt ("F", p) -> (* F -> ( R ) | id | lit *)
      match p with
	  | [PT_num (num)] -> AST_num (num)
	  | (* code for id *)
	  | (* code for ( R ) *)
	  | _ -> raise (Failure "malformed F parse tree in ast_ize_expr")
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr")

and ast_ize_reln_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs is an inherited attribute.
     tail is an ET parse tree node *)
  match tail with
  | PT_nt ("ET", []) -> lhs  (* ET -> epsilon *)
  | (* ET -> ro E *) )
  | _ -> raise (Failure "malformed parse tree in ast_ize_reln_tail")

and ast_ize_expr_tail (lhs:ast_e) (tail:parse_tree) : ast_e =
  (* lhs is an inherited attribute.
     tail is a TT or FT parse tree node *)
  match tail with
  | PT_nt ("TT", []) -> lhs (* TT -> epsilon *)
  | (* TT -> ao T TT *)
  | PT_nt ("FT", []) -> lhs  (* FT -> epsilon *)
  | (* FT -> mo F FT *)
  | _ -> raise (Failure "malformed parse tree in ast_ize_expr_tail")
;;


(* "Hand build" a parse tree for part of the sum_ave_prog *)

let stmt1 = PT_nt ("S", [PT_term "read"; PT_id ("a")]);;

let stmt2 = PT_nt ("S", [PT_term "read"; PT_id ("b")]);;

let rhs = PT_nt ("R",
           [PT_nt ("E",
             [PT_nt ("T",
               [PT_nt ("F", [PT_id ("a")]);
                PT_nt ("FT", [])]);
              PT_nt ("TT",
               [PT_nt ("ao", [PT_term ("+")]);
                PT_nt ("T",
                 [PT_nt ("F", [PT_id ("b")]);
                  PT_nt ("FT", [])]);
                PT_nt ("TT", [])])]);
			PT_nt ("ET", [])]);;
				
let stmt3 = PT_nt ("S", [PT_id ("sum"); PT_term (":="); rhs]);;

let stmtn = PT_nt ("S", [PT_id ("sum"); PT_term (":="); PT_id ("c")]);;

let stmtGT = PT_nt
       ("S",
        [PT_term "check";
         PT_nt
          ("R",
           [PT_nt
             ("E",
              [PT_nt ("T", [PT_nt ("F", [PT_id "n"]); PT_nt ("FT", [])]);
               PT_nt ("TT", [])]);
            PT_nt
             ("ET",
              [PT_nt ("ro", [PT_term ">"]);
               PT_nt
                ("E",
                 [PT_nt ("T", [PT_nt ("F", [PT_num "0"]); PT_nt ("FT", [])]);
                  PT_nt ("TT", [])])])])]);;

(* ast_ize_S stmt1;; *)

(* ast_ize_S stmtn;; *)

let stmt_list = [];;
let sl = append (append (append stmt_list [stmt1]) [stmt2]) [stmt3];;

let simpleProg = PT_nt
 ("P",
  [PT_nt
    ("SL",
     [PT_nt
       ("S",
        [PT_id "sum"; PT_term ":=";
         PT_nt
          ("E",
           [PT_nt ("T", [PT_nt ("F", [PT_id "a"]); PT_nt ("FT", [])]);
            PT_nt
             ("TT",
              [PT_nt ("ao", [PT_term "+"]);
               PT_nt ("T", [PT_nt ("F", [PT_id "b"]); PT_nt ("FT", [])]);
               PT_nt ("TT", [])])])]);
      PT_nt
       ("SL",
        [PT_nt
          ("S",
           [PT_term "check";
            PT_nt
             ("R",
              [PT_nt
                ("E",
                 [PT_nt ("T", [PT_nt ("F", [PT_id "n"]); PT_nt ("FT", [])]);
                  PT_nt ("TT", [])]);
               PT_nt
                ("ET",
                 [PT_nt ("ro", [PT_term ">"]);
                  PT_nt
                   ("E",
                    [PT_nt
                      ("T", [PT_nt ("F", [PT_num "0"]); PT_nt ("FT", [])]);
                     PT_nt ("TT", [])])])])]);
         PT_nt ("SL", [])])]);
   PT_term "$$"]);;
  