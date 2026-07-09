How to test the translate functions
===================================

The simplest way to test the individual translate functions is to build a simple AST node of the appropriate type “by hand”, then call the respective translate function with your new node.

For example:

let s1 = AST_assign ("x", AST_id ("y"));; (* x := y *)
translate_assign s1;;

let s2 = AST_write (AST_binop ("+", AST_id ("a"), AST_num ("2")));; (* write a+2 *)
translate_write s2;;