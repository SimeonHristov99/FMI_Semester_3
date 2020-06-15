#include <iostream>

template <class T>
size_t partition(T* arr, int low, int high)
{
	T pivot = arr[high];

	size_t partition_index = low;

	for (size_t i = low; i < high; i++)
	{
		if (arr[i] <= pivot)
		{
			std::swap(arr[i], arr[partition_index]);
			++partition_index;
		}
	}

	std::swap(arr[partition_index], arr[high]);

	return partition_index;
}

template <class T>
void quick_sort(T* arr, int low, int high)
{
	if (low < high)
	{
		size_t p_index = partition(arr, low, high);

		quick_sort(arr, low, p_index - 1);
		quick_sort(arr, p_index + 1, high);
	}
}

template <class T>
void quick_sort(T* arr, const size_t size)
{
	quick_sort(arr, 0, size - 1);
}

int main()
{
	int arr[10] = { 66, 51,  0,  5, 42, 92,  8,  8, 28,  8 };
	int arr2[8] = { 2, 6, 5, 3, 8, 7, 1, 0 };

	quick_sort(arr, 10);
	quick_sort(arr2, 8);

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