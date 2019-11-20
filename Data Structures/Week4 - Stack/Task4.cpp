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

bool has_bigger_priority(char from, char candidate)
{
	if (from == '*' || from == '/')
	{
		return false;
	}

	return true;
}

int calculate_RPN(const char* expression)
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

int evaluate(const char* expression)
{
	Stack<char> operations;

	char expr2[1024] = { '\0' };

	size_t i = 0;

	for (const char* c = expression; *c; c++)
	{
		if (is_digit(*c))
		{
			while (is_digit(*c))
			{
				expr2[i++] = *c;
				++c;
			}

			expr2[i++] = ',';
		}

		if (is_operation(*c))
		{
			if (operations.is_empty())
			{
				operations.push(*c);
			}
			else if (has_bigger_priority(operations.top(), *c))
			{
				operations.push(*c);
			}
			else
			{
				while (!has_bigger_priority(operations.top(), *c))
				{
					expr2[i++] = operations.top();
					operations.pop();
				}

				operations.push(*c);
			}
		}
		else if (*c == '(')
		{
			operations.push(*c);
		}
		else if (*c == ')')
		{
			while (operations.top() != '(')
			{
				expr2[i++] = operations.top();
				operations.pop();
			}

			operations.pop();
		}
	}

	while (!operations.is_empty())
	{
		expr2[i++] = operations.top();
		operations.pop();
	}

	return calculate_RPN(expr2);
}

int main()
{
	const char* expression = "1*2*3+2/1+4*8+(2-3)";

	std::cout << evaluate(expression) << std::endl;

	return 0;
}