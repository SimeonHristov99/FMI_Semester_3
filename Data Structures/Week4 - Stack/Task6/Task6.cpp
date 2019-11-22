#include <iostream>
#include "Stack.hpp"

void decompress(const char* expression)
{
	Stack<int> numbers;
	Stack<char> letters;

	for (const char* c = expression; *c; ++c)
	{
		if (*c > '1' && *c <= '9')
		{
			numbers.push(*c - '0');
		}
		else if (*c == ')')
		{
			Stack<char> repeated;

			Stack<char> to_repeat;
			
			unsigned times_to_repeat = numbers.top();
			numbers.pop();

			while (letters.top() != '(')
			{
				to_repeat.push(letters.top());
				letters.pop();
			}

			letters.pop();

			// Make the copy ctor and op=.
			// Make a copy of to_repeat.
			// Dump the copy in repeated while times_to_repeat > 1.
			// Dump to_repeat in repeated.
		}
		else
		{
			letters.push(*c);
		}
	}

	if (numbers.is_empty() || letters.is_empty())
	{
		std::cout << expression << std::endl;
	}
}

int main()
{
	const char* expression = "2(AB2(CD))";

	decompress(expression);

	return 0;
}