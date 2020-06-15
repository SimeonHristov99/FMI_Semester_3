#include <iostream>
#include "Stack.hpp"

int evaluate(const char* expression)
{
	Stack<char> operations;
	Stack<int> numbers;
	Stack<int> numbers2;

	for (const char* c = expression; *c; ++c)
	{
		if (*c >= '0' && *c <= '9')
		{
			numbers.push(*c - '0');
		}
		else if (*c == ')')
		{
			while (operations.top() != '+' && operations.top() != '*')
			{
				// Pop the ',' or '('. Transfer the top of numbers to numbers2.
				operations.pop();
				numbers2.push(numbers.top());
				numbers.pop();
			}

			while (!numbers2.is_empty())
			{
				int b = numbers2.top();
				numbers2.pop();

				if (numbers2.is_empty())
				{
					numbers.push(b);
				}
				else
				{
					int a = numbers2.top();
					numbers2.pop();

					if (operations.top() == '*')
					{
						numbers2.push(a * b);
					}
					else // == '+'
					{
						numbers2.push(a + b);
					}
				}
			}

			operations.pop();
		}
		else // *c == '+' || '-' || '(' || ','
		{
			operations.push(*c);
		}
	}

	return numbers.top();
}

int main()
{
	const char* expression = "+(*(2,3),4,+(4,5,6))";

	std::cout << evaluate(expression) << std::endl;

	return 0;
}