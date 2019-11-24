#include <iostream>
#include "Stack.hpp"

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

void bracketfy(char* expression)
{
	Stack<char> container;

	for (const char* c = expression; *c; ++c)
	{
		container.push(*c);
	}

	Stack<char> result;
	unsigned opening_brackets = 0;

	while (!container.is_empty())
	{
		char current = container.top();
		container.pop();

		if (is_digit(current))
		{
			result.push(current);
		}
		else if (current == '+' || current == '-' || current == '*' || current == '/')
		{
			result.push(current);

			char next = container.top();
			container.pop();

			if (is_digit(next))
			{
				result.push(next);
				result.push('(');
				--opening_brackets;
			}
			else // It is a closing bracket.
			{
				result.push(next);

				++opening_brackets;
			}
		}
		else // It is a closing braket.
		{
			result.push(current);
			++opening_brackets;
		}
	}

	while (opening_brackets > 0)
	{
		result.push('(');

		--opening_brackets;
	}

	size_t i = 0;

	for (; !result.is_empty(); ++i)
	{
		expression[i] = result.top();
		result.pop();
	}

	expression[i] = '\0';
}

int main()
{
	char expression[50] = "5+6)*4+2))/8)*2+5))";

	bracketfy(expression);

	// Should be: ((((5+6)*(4+2))/8)*(2+5)). 6 missed opening brackets.
	std::cout << expression << std::endl;

	return 0;
}