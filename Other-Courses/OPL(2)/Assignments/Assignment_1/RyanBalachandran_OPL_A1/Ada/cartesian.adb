with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Cartesian is

   -- DECLARATIONS (TYPES AND VARS):

   aLimit : Integer := 4;
   bLimit : Integer := 3;
   cLimit : Integer := aLimit * bLimit;

   cIndex : Integer;
   lineCount : Integer;

   TYPE AP is array(0..aLimit) of Integer;
   TYPE EP is array(0..bLimit) of Integer;
   type CP is array(0..cLimit) of Integer;
   a : AP;
   b : EP;
   c : CP;


begin

   Ada.Text_IO.Put_Line ("");
   Ada.Text_IO.Put_Line ("Cartesian Product using Ada:");
   Ada.Text_IO.Put_Line ("");
   --Ada.Text_IO.Put_Line ("");

  -- setup: initialize input arrays with simple values:
   for i in 1 .. aLimit loop
      a(i) := i;
   end loop;

   Put_Line ("Display values for first array: ");
   for i in 1 .. aLimit loop
      Put(a(i));
   end loop;
   Put_Line ("");






   for i in 1 .. bLimit loop
      b(i) := i;
   end loop;

   Put_Line ("Display values for second array: ");
   for i in 1 .. bLimit loop
      Put(b(i));
   end loop;





   -- compute Cartesion product:
   cIndex := 1;
   for i in 1 .. aLimit loop
      for j in 1 .. bLimit loop
         c(cIndex) := a(i) * b(j);
         cIndex := cIndex + 1;
      end loop;
   end loop;

   -- display Cartesian product:
   Put_Line ("");
   Put_Line ("");
   Put_Line ("Cartesian product of the input arrays: ");
   lineCount := 0;
   for i in 1 .. cLimit loop
      Put(c(i));
      lineCount := lineCount + 1;
      if lineCount = bLimit then
         lineCount := 0;
         Put_Line ("");
      end if;
   end loop;


   Put_Line ("");
   Put_Line ("");
   Put_Line ("Procedure terminated without exception.");
   Put_Line ("");


end Cartesian;
