#include <iostream>

template <class T>
void merge(T* arr1, size_t s1, T* arr2, size_t s2, T* result)
{
	size_t i = 0;

	size_t j = 0;
	size_t k = 0;

	while (j < s1 && k < s2)
	{
		if (arr1[j] < arr2[k])
		{
			result[i] = arr1[j];
			++j;
		}
		else
		{
			result[i] = arr2[k];
			++k;
		}

		++i;
	}

	while (j < s1)
	{
		result[i] = arr1[j];
		++j;
		++i;
	}

	while (k < s1)
	{
		result[i] = arr2[k];
		++k;
		++i;
	}
}

template <class T>
void merge_sort(T* arr, const size_t size)
{
	if (size == 1)
	{
		return;
	}

	T* left = new T[size / 2 + 1];
	for (size_t i = 0; i < size / 2; i++)
	{
		left[i] = arr[i];
	}

	T* right = new T[size / 2 + 1];
	for (size_t i = size/2; i < size; i++)
	{
		right[i - size/2] = arr[i];
	}

	merge_sort(left, size/2);
	merge_sort(right, size/2);
	merge(left, size/2, right, size / 2, arr);

	delete[] right;
	delete[] left;
}

int main()
{
	int arr[10] = { 66, 51,  0,  5, 42, 92,  8,  8, 28,  8 };
	int arr2[8] = { 2, 6, 5, 3, 8, 7, 1, 0 };

	merge_sort(arr, 10);
	merge_sort(arr2, 8);

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