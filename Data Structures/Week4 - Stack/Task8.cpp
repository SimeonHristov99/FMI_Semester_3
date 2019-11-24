#include <iostream>
#include "Stack.hpp"

// Assuming the numbers are integers and that the size is also given when calling the function.
void print_bigger(const int* arr, const size_t size)
{
	Stack<int> input;
	Stack<int> result;

	// Input the fist digit.
	input.push(*arr);

	for (size_t i = 1; i < size; i++)
	{
		if (arr[i] <= input.top())
		{
			input.push(arr[i]);
		}
		else
		{
			while (arr[i] > input.top() && !input.is_empty())
			{
				result.push(arr[i]);
				result.push(input.top());
				input.pop();
			}

			input.push(arr[i]);
		}
	}

	while (!input.is_empty())
	{
		result.push(-1);
		result.push(input.top());
		input.pop();
	}

	while (!result.is_empty())
	{
		std::cout << result.top() << ' ';
		result.pop();
		std::cout << result.top() << std::endl;
		result.pop();
	}
}

int main()
{
	int arr[12] = { 4, 5, 100, 200, -1, 8, 7, 7, 6, 88, 94, -74 };

	print_bigger(arr, 12);

	return 0;
}