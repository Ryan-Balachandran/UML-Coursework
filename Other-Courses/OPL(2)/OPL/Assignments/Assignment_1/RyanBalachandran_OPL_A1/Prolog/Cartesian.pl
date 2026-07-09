:- initialization(main1).
:- initialization(main2).
:- initialization(main3).
:- initialization(main4).
:- initialization(main5).
:- use_module(library(chr)).

main1 :-
    product([1,2], [3, 4], X),
    writeln(X).

main2 :-
    product([3, 4], [1, 2], X),
    writeln(X).

main3 :-
    product([1,2], [], X),
    writeln(X).

main4 :-
    product([], [1, 2], X),
    writeln(X).

main5 :-
    product([1, 2, 3], [a, b, c, d], X),
    writeln(X).

product(A,B,C) :- findall([X,Y],(member(X,A),member(Y,B)),C).


/*
    In Terminal:
        prolog
            [user]
            set rules
            Control + D to exit and compile
    To run:
        product([number,...], [number,...], C).
*/
