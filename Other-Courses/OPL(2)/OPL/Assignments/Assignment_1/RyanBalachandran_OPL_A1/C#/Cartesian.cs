// C# program of Cartesian Product

using System;
using System.Linq;
using System.Collections.Generic;

public class CartesianProduct
{
	public static void Main()
	{
		int[] emptyset = new int[0];	//Empty set/array
		int[] set1 = {1, 2};		    //Array(set) of two integers
		int[] set2 = {3, 4};		    //Array(set) of two integers
        int[] set3 = {5, 6, 7};         //Array(set) of two integers

        Console.WriteLine("\nGenerate a Cartesian Produce of two or more sets: \n");

		//for loop: create a new array that contains the given two or more sets
		foreach (var arrayset in new [] {
			new [] {set1, set2},
			new [] {set2, set1},
			new [] {set1, emptyset},
			new [] {emptyset, set1},
			new [] {set2, emptyset},
			new [] {emptyset, set2},
            new [] {set3, set1} })
		{
			//variable cartesian that calls Cartesian Product function to cacatenate each element
            //in the first set with each element in the second or subsequent sets
			var cartesian = arrayset.CartesianProduct().Select(tuple => $"({string.Join(", ", tuple)})");	
			Console.WriteLine($"{{{string.Join(", ", cartesian)}}}");
		} 
	}
}


public static class Extensions
{	
	//Template for cartesian product
	public static IEnumerable<IEnumerable<T>> CartesianProduct<T>(this IEnumerable<IEnumerable<T>> sequences) 
	{
        	IEnumerable<IEnumerable<T>> emptyProduct = new [] {Enumerable.Empty<T>()};
        	return sequences.Aggregate(
			emptyProduct, 
			(accumulator, sequence) => 
			from acc in accumulator 
			from item in sequence 
			select acc.Concat(new [] {item}));
    }
}








