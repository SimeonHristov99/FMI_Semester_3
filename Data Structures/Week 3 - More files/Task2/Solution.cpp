#include <iostream>
#include <fstream>

// Get the number formed by all digits in a file.

double make_number(const char* path)
{
	double number = 0;

	std::ifstream fin(path);

	if (fin)
	{
		char current;

		while (fin)
		{
			fin.read(&current, 1);
			if (fin)
			{
				if (current >= '0' && current <= '9')
				{
					int temp = current - '0';
					number = number * 10 + (double) temp;
				}
			}
		}

		fin.close();

		return number;
	}

	std::cout << "\n\tCould not open file.txt! Returning 0";
	return 0;
}

// Get the name which has the highest number against it.

size_t get_max_index(const unsigned* arr, const size_t& size) // Return the row which has the biggest number.
{
	unsigned max_index = 0;

	for (size_t j = 1; j < size; j++)
	{
		if (arr[max_index] < arr[j])
		{
			max_index = j;
		}
	}

	return max_index;
}

void highest_name(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		unsigned number[2048] = { 0 };
		size_t row_count = 0;

		char current;

		while (fin)
		{
			fin.read(&current, 1);

			if (current >= '0' && current <= '9')
			{
				do
				{
					number[row_count] = number[row_count] * 10 + (current - '0');
					fin.read(&current, 1);
					if (fin && current == '\n')
					{
						++row_count;
					}
				} while (current >= '0' && current <= '9' && fin);
			}
			else if (current == '\n')
			{
				++row_count;
			}
		}

		size_t max_row = get_max_index(number, row_count + 1);

		fin.close(); // Move to the beginning from the current position.
		fin.open(path);

		unsigned current_row = 0; // Move to the row which has the maximum number in it.

		while (current_row != max_row)
		{
			fin.read(&current, 1);

			if (fin)
			{
				if (current == '\n')
				{
					++current_row;
				}
			}
		}

		while (fin)
		{
			fin.read(&current, 1); // Start looking for the name - a word with a capital letter.

			if (fin)
			{
				if (current >= 'A' && current <= 'Z')
				{
					do
					{
						std::cout << current;
						fin.read(&current, 1);
					} while (fin && current >= 'a' && current <= 'z');
				}
				else if (current == '\n')
				{
					fin.close();
					return;
				}
			}
		}

		fin.close();
		return;
	}

	std::cout << "\n\tCould not open file.txt!";
}

int main()
{
	const char* path = "file.txt";

	std::cout << make_number(path) << std::endl;

	highest_name(path);

	return 0;
}