# Tasks

Task1: Write a static implementation of a stack using a template.

Task2: Write a program which reads from a file a string of brakets, i.e. '(', ')', '[', ']', '{', '}'. The program returns a True if the brakets are balanced and False, otherwise.

Task3: Evaluate a mathematical expression written in reverse polish notation.

Task4: Evaluate an expression in infix notation using the Shunting Yard Algorithm.

Task5: Given an expression with the following grammar  
  * formula = digit | operation(formula, formulas)  
  * formulas = formula | formula, formulas  
  * operation = + | *  
  * digit = 0|1|…|9</ul></li>
Evaluate the expression. 
Example. The value of +(*(2,3), 4, +(4,5,6)) is 25.

Task6:
	Write a programm that "decompresses" a given string.
	The compressed string may contain 2 things:
	 letters from A to Z that are decompressed to the same letter 
	 A group which is a number N followed by another group in brackets which is decompressed to the 	group in the brackets N times.
	Examples:
	A -> A
	AB -> AB
	3(A) -> AAA
	3(AB2(B)) -> ABBBABBBABBB
	12(ZQ) -> ZQZQZQZQZQZQZQZQZQZQZQZQ

Task7:
	Given an expression with the following grammar:
		<expression> := <digit> | (<digit><operation><digit>)
		<digit> := 0|1|2...|9
		<operation> := *|+|-|/
	The expression is missing all of its opening brackets but is otherwise correct.
	Fix the expression.

Task8:
	Given an array of numbers, for every number print it and the first larger number after it. If there isn't one print -1
	Example:
	Input 4 2 1 3
	Output:
		4 -1
		2 3
		1 3
		3 -1

Task9:
	Stock Span Problem
		You are given an array of numbers. For every index in the array, print the number of consecutive numbers in the array (ending at that index) that are not bigger than the given number
	Example:
		Input:  5 2 3 7 6 4
		Output: 1 1 2 4 5 1 

Task10:
	Maximum area in histogram
		You are given an array of numbers representing heights of rectangulars with width 1. The recangulars are directly next to each other. Calculate the area of the largest possible recantgle you can cut from the given ones. (e.g. from a triangle with height 3 and one with height 4, you can cut out one with height 3 and width 2)
	Example
		2 1 4 5 1 3 3 -> 8 (you can cut 2 parts of 4 from the rectangles with height 4 and 5)
		10 10 10 10 -> 40 (the whole figure is a rectangle)