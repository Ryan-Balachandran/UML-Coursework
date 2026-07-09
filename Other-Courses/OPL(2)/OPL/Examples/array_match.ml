(* Examples of matching on an array *)

let f1 a =
	match a with
	| [| |] -> -1
	| [| x |] -> x
	| [| x; y |] -> x+y
	| _ -> 1000;;
	
let f2 a =
	match a with
	| [| |] -> "none"
	| [| _ |] -> "one"
	| [| _; _ |] -> "two"
	| _ -> "three or more";;
