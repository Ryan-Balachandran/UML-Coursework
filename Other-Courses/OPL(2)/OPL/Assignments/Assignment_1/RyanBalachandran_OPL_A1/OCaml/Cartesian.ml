(*Ocaml program of Cartesian Product*)

let rec product l1 l2 =                                                         (*recursive function of two inputs*)
    match l1, l2 with                                                           (*match elements in input 1 with input 2*)
    | [], _ | _, [] -> []                                                       (*rules for producing the product of a set with the empy set*)
    | h1::t1, h2::t2 -> (h1,h2)::(product [h1] t2)@(product t1 l2);;

product [1;2] [3;4];;
(*- : (int * int) list = [(1, 3); (1, 4); (2, 3); (2, 4)]*)

product [3;4] [1;2];;
(*- : (int * int) list = [(3, 1); (3, 2); (4, 1); (4, 2)]*)

product [1;2] [];;
(*- : (int * 'a) list = []*)

product [] [1;2];;
(*- : ('a * int) list = []*)

product ['a';'b'] [1;2];;
(*- : (char * int) list = [('a', 1); ('a', 2); ('b', 1); ('b', 2)]*)

product ["dog";"cat";"bird"] ["bark";"meow";"chirp"];;
(*- : (string * string) list = []*)






(* Terminal input: product [#,#] [#,#] *)