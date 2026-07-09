(* Syntax tree nodes representing simple integer expresssions *)

type expression =
    | Num of int
    | Unary_op of string * expression
    | Binary_op of string * expression * expression;;


(* Evaluation function for our syntax tree *)

let rec eval env = function
  | Num i -> i
  | Unary_op (op, e) ->
      let v = eval env e in
        eval_unary_op op v
  | Binary_op (op, e1, e2) ->
      let v1 = eval env e1 in
      let v2 = eval env e2 in
        eval_binary_op op v1 v2
and eval_unary_op op v =
  match op with
    | "+" -> v
    | "-" -> -v
    | _ -> failwith ("Unknown unary operator: " ^ op)
and eval_binary_op op v1 v2 =
  match op with
    | "+" -> v1 + v2
    | "-" -> v1 - v2
    | "*" -> v1 * v2
    | "/" -> v1 / v2
    | _ -> failwith ("Unknown binary operator: " ^ op);;


(* Some sample expressions *)

eval [] (Binary_op ("*", Num 2, Num 4));;  (* 2*4 *)

eval [] (Unary_op ("-", (Binary_op ("*", Num 3, Num 6))));;  (* -(3*6) *)

eval [] (Binary_op ("+", (Binary_op ("*", Num 3, Num 4)), Num 5));;  (* 3*4+5 *)

eval [] (Unary_op ("*", Num 2));; (* Unknown unary operator *)

eval [] (Binary_op ("%", Num 2, Num 4));; (* Unknown binary operator *)
