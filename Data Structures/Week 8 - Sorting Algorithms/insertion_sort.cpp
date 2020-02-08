#include <iostream>

template <class T>
void insertion_sort(T* arr, const size_t size)
{
	for (size_t i = 1; i < size; i++)
	{
		int j = i;

		while (j > 0 && arr[j] < arr[j - 1])
		{
			std::swap(arr[j], arr[j - 1]);
			--j;
		}
	}
}

int main()
{
	int arr[10] = { 66, 51,  0,  5, 42, 92,  8,  8, 28,  8 };
	int arr2[8] = { 2, 6, 5, 3, 8, 7, 1, 0 };

	insertion_sort(arr, 10);
	insertion_sort(arr2, 8);

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << arr[i] << ' ';
	}

	std::cout << '\n';
	
	for (size_t i = 0; i < 8; i++)
	{
		std::cout << arr2[i] << ' ';
	}

    return 0;
}