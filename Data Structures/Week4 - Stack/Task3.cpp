#include <iostream>

#include "Stack.hpp"

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

bool is_operation(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int evaluate(const char* expression)
{
	Stack<int> numbers;
	Stack<char> operations;

	for (const char* c = expression; *c; ++c)
	{
		if (is_digit(*c))
		{
			int number = 0;
			while (is_digit(*c))
			{
				number = number * 10 + (*c - '0');
				++c;
			}

			numbers.push(number);
		}

		if (is_operation(*c))
		{
			int b = numbers.top();
			numbers.pop();
			int a = numbers.top();
			numbers.pop();

			switch (*c)
			{
			case '+':
			{
				numbers.push(a + b);
				break;
			}
			case '-':
			{
				numbers.push(a - b);
				break;
			}
			case '*':
			{
				numbers.push(a * b);
				break;
			}
			case '/':
			{
				if (b == 0)
				{
					std::cout << "Dividing by 0! Returning 0.\n";
					return 0;
				}
				else
				{
					numbers.push(a / b);
				}
			}
			}
		}
	}

	int result = numbers.top();
	numbers.pop();
	return result;
}

int main()
{
	const char* expression = "592*+";

	std::cout << evaluate(expression) << std::endl;

	return 0;
}