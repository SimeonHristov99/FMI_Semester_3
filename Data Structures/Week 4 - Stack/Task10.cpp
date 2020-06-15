#include <iostream>
#include "Stack.hpp"

size_t max_area(const unsigned* arr, const size_t size)
{
	size_t result = 0;

	Stack<size_t> positions;

	for (size_t i = 0; i < size; i++)
	{
		if(positions.is_empty() || arr[positions.top()] <= arr[i])
		{
			positions.push(i);
		}
		else
		{
			while (!positions.is_empty() && arr[positions.top()] > arr[i])
			{
				unsigned current = positions.top();
				positions.pop();

				size_t candidate_area = 0;

				if (positions.is_empty())
				{
					candidate_area = arr[current] * i;
				}
				else
				{
					candidate_area = arr[current] * (i - positions.top() - 1);
				}

				result = (candidate_area > result ? candidate_area : result);
			}

			positions.push(i);
		}
	}

	while (!positions.is_empty())
	{
		size_t current = positions.top();
		positions.pop();

		size_t candidate_area = 0;

		if (positions.is_empty())
		{
			candidate_area = arr[current] * size;
		}
		else
		{
			candidate_area = arr[current] * (size - positions.top() - 1);
		}

		result = (candidate_area > result ? candidate_area : result);
	}

	return result;
}

int main()
{
	unsigned arr[2] = { 2, 1 };

	std::cout << max_area(arr, 2) << std::endl;

	return 0;
}