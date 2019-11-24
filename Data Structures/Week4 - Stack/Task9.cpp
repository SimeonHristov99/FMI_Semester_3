#include <iostream>
#include "Stack.hpp"

// Assuming numbers that size is also given when calling the function.
void stock_span(const unsigned* arr, const size_t size)
{
	Stack<unsigned> input;
	Stack<size_t> result;

	for (size_t i = 0; i < size; i++)
	{
		input.push(arr[i]);
	}

	while (!input.is_empty())
	{
		unsigned current = input.top();
		input.pop();

		size_t bigger = 1;

		Stack<unsigned> poped_elements;
		
		while (input.top() <= current && !input.is_empty())
		{
			poped_elements.push(input.top());
			input.pop();

			++bigger;
		}

		result.push(bigger);

		while (!poped_elements.is_empty())
		{
			input.push(poped_elements.top());
			poped_elements.pop();
		}
	}

	while (!result.is_empty())
	{
		std::cout << result.top() << ' ';
		result.pop();
	}
}

int main()
{
	unsigned arr[7] = { 100, 80, 60, 70, 60, 75, 85 };

	stock_span(arr, 7);

	return 0;
}