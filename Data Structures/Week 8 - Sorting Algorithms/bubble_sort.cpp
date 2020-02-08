#include <iostream>

void bubble_sort(int* arr, const size_t& size)
{
	bool swapped = true;

	while (swapped)
	{
		swapped = false;

		for (int i = size - 1; i > 0; --i)
		{
			if (arr[i] < arr[i - 1])
			{
				int temp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = temp;

				swapped = true;
			}
		}
	}
}

int main()
{
	int arr[10] = { 66, 51,  0,  5, 42, 92,  8,  8, 28,  8 };

	bubble_sort(arr, 10);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << arr[i] << ' ';
	}

    return 0;
}