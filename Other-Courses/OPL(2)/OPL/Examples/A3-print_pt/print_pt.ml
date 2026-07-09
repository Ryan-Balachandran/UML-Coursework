(* Uncomment the following line if you want to #use "myParser.ml";; *)
(* in the Ocaml interpreter:                                        *)
#use "myParser.ml";;

(* Uncomment the following 2 lines if you want to load the   *)
(* precompiled myParser.cmo module in the Ocaml interpreter: *)
(* #load "myParser.cmo";; *)
(* open MyParser;; *)

(* Uncomment the following line if you are using the ocamlopt compiler *)
(* to compile/link myParser.o and print_pt.o together into a           *)
(* native executable:                                                  *)
(* open myParser;; *)


let rec print_parse_tree pt =
	print_string (stringify_parse_tree 0 pt)
and stringify_parse_tree level = function
	| PT_error -> "PT_error"
	| PT_id id -> "PT_id \"" ^ id ^ "\""
	| PT_num num -> "PT_num \"" ^ num ^ "\""
	| PT_term term -> "PT_term \"" ^ term ^ "\""
	| PT_nt (nt, lst) ->
	    match lst with
		| [] -> "PT_nt (\"" ^ nt ^ "\", [])"
		| _ ->
		    let sptl = stringify_parse_tree_list (succ (succ level)) lst in
		    let sp = String.make (succ level) ' ' in
		    match nt with
		    | "S" | "F" | "mo" | "ao" | "ro" -> "PT_nt (\"" ^ nt ^ "\", [" ^ sptl ^ "])"
		    | _ -> "PT_nt (\"" ^ nt ^ "\",\n" ^ sp ^ "[" ^ sptl ^ "])"
and stringify_parse_tree_list level ptl =
  match ptl with
  | [] -> ""
  | head::[] -> stringify_parse_tree level head
  | head::rest ->
	  let sep = 
	    match head with
		| (PT_term "read") -> "; "
		| _ -> ";\n" ^ (String.make level ' ') in
	  let spt_head = stringify_parse_tree level head in
	  let sptl_rest = stringify_parse_tree_list level rest in
        spt_head ^ sep ^ sptl_rest;;

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

let sum_ave_prog = "
  read a
  read b
  sum := a + b
  write sum
  write sum / 2";;

let sap = parse ecg2_parse_table sum_ave_prog;;
print_parse_tree sap;;

(* let pp = parse ecg2_parse_table primes_prog;; *)
(* print_parse_tree pp;; *)
