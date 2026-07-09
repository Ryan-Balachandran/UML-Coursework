let rec fact x =
  if x <= 1 then 1
  else x * fact (x-1);;

fact 4;;

(* #trace fact;; *)


let compose f g = fun x -> f (g x);;

let rec power f n = 
  if n = 0 then fun x -> x 
  else compose f (power f (n - 1));;

let derivative dx f = fun x -> (f (x +. dx) -. f x) /. dx;;


let sin' = derivative 1e-5 sin;; (* = cos *)

let cos' = derivative 1e-5 cos;; (* = -sin *)

let sin''' = power (derivative 1e-5) 3 sin;; (* = -cos *)


(* https://en.wikipedia.org/wiki/Trigonometric_functions#/media/File:Sine_cosine_one_period.svg *)

let pi = 4.0 *. atan 1.0;;

sin 0.0;;

cos' 0.0;;

sin (pi /. 2.);;

cos' (pi /. 2.);;

cos (pi /. 2.);;

sin' (pi /. 2.);;

sin' pi;;

cos pi;;

sin''' pi;;

