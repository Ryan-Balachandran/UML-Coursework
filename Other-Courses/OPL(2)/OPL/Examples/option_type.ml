(* List maximum function for integers; uses flag value to indicate invalid return value *)
let rec list_max_int l =
	match l with
	| head::tail -> max head (list_max_int tail)
	| [] -> min_int;; (* flag value to indicate invalid return value *)


(* Generic list maximum function; uses option type to indicate invalid return value *)
let rec list_max l =
	match l with
	| head::tail ->
		begin
			match list_max tail with
			| None -> Some head
			| Some m -> Some (max head m)
		end
	| [] -> None;;


(* "Safe" division for integers; uses option type to indicate invalid return value *)
let safedivide_int x y =
	match y with
	| 0 -> None
	| _ -> Some (x / y);;


(* A function to get the value associated with any option type.             *)
(* In OCaml 4.08 or higher, this is builtin as the function Option.get      *)
(* <https://caml.inria.fr/pub/docs/manual-ocaml/libref/Option.html>         *)
let extract x =
	match x with
	| Some v -> v
	| None -> raise (Invalid_argument "in extract");;


(***** WARNING: Everything below this point is advanced OCaml. *****)
(*****                May make your head explode!              *****)


(* Generic division function using polymorphic variants:                    *)
(* <https://blog.klipse.tech/ocaml/2018/03/16/ocaml-polymorphic-types.html> *)
(* <http://dev.realworldocaml.org/variants.html#polymorphic-variants>       *)
let divide x y =
	match x with
	| `Int xx ->
		begin
			match y with
			| `Int yy -> `Int(xx / yy)
			| `Float yy -> `Float((float_of_int xx) /. yy)
		end
	| `Float xx ->
		begin
			match y with
			| `Int yy -> `Float(xx /. (float_of_int yy))
			| `Float yy -> `Float(xx /. yy)
		end;;

(* Try it out. *)
let o1 = `Int(10);;
let o2 = `Int(2);;
let o3 = `Float(10.0);;
let o4 = `Float(2.0);;

divide o1 o2;;
divide o3 o4;;
divide o1 o4;;
divide o3 o2;;


(* Generic "safe" division function, combines option types and polymorphic variants *)
let safedivide x y =
    match y with
	| `Int z when z=0 -> None
	| `Float z when z=0.0 -> None
	| _ -> Some (divide x y);;

(* Try it out. *)
let o5 = `Int(0);;
let o6 = `Float(0.0);;

safedivide o1 o2;;
safedivide o3 o4;;
safedivide o1 o4;;
safedivide o3 o2;;
safedivide o1 o5;;
safedivide o1 o6;;
safedivide o3 o5;;
safedivide o3 o6;;
