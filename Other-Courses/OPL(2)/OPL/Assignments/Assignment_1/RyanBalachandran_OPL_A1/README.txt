- What was easy?
    -Ruby and C# were the easiest to code in.

- What was hard?
    - Ocaml was hard to figure out how to compile
    - Ada was very difficult to learn how to make arrays and how to pair the arrays into a cartesian product
    - Prolog was difficult at first to understand how to run a file from the command line

- Are there noticeable differences in speed?
    - There was no noticeable difference in speed when running or compiling the file

- What do you like/dislike?
    - I do not like how complicated Ada is

- Did you use polymorphism in one or more of your programs? If YES, specify which
one(s), and comment on whether it was easy or hard to make use of polymorphism in the respective language(s).
    - I did not use Polymorphism in any of my programs (I don't think)





Here is how I ran/compiled each program in each language:

- For Ruby: in the command line terminal, I typed: ruby Cartesian.rb 

- For C#: in the command line terminal, I typed the following to make the executable: mcs Cartesian.cs
    - I then typed the following to run the executable: mono Cartesian.exe

- For Ocaml: I did not know how to compile the code and link the files, so in the command line terminal, I typed the following: ocaml < Carttesian.ml

- For Prolog: in the command line terminal in the same directory of the file, I typed the following: product([1, 2], [3, 4], X)
    - I also downloaded SWI-PROLOG on my Mac laptop, went to file -> consult, and selected the file, where it then compiled and displayed the Cartesian products 

- For Ada: in the command line terminal, I typed the following: gnatmake -o Cartesian Cartesian.adb
    - I then typed the following to run the executable: ./Cartesian
