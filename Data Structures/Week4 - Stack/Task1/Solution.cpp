// A linked implementation of a stack.

#include "Stack.h"

#include <iostream>

int main()
{
	Stack<char> alphabet;

	for (char c = 'a'; c <= 'z'; c++)
	{
		alphabet.push(c);
	}

	std::cout << "The english alphabet in reverse order is: ";

	while (!alphabet.is_empty())
	{
		std::cout << alphabet.pop() << ' ';
	}

	std::cout << '\n';

	return 0;
}