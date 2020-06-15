#include <iostream>
#include <fstream>

// Write in console. Write to file. Output file content.

void write_to_file(const char* path)
{
	std::ofstream fout(path);

	if (fout)
	{
		char text[1024];

		while (std::cin.get(text, '\n'))
		{
			fout << text;
		}
	}

	fout.close();

	std::ifstream fin(path);

	if (fin)
	{
		char text[1024];

		while (fin.get(text, '\n'))
		{
			std::cout << text;
		}
	}

	fin.close();
}

// By given stream and file determine the number of rows.

size_t number_rows(std::ifstream& fin, const char* path)
{
	size_t count_rows = 1;

	if (fin)
	{
		char c;

		while (fin)
		{
			fin.read(&c, 1);
			if (fin)
			{
				if (c == '\n')
				{
					++count_rows;
				}
			}
		}

		fin.close();

		return count_rows;
	}
	
	std::cout << "\n\tCould not open file" << std::endl;

	return -1;
}

// Get the size of a file.

std::streamoff file_size(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		fin.seekg(0, std::ios::end);
		return fin.tellg();
	}

	std::cout << "\n\tCould not open file" << std::endl;

	return -1;
}

// Read from a file with 4 rows of 2 numbers. Calculate the area of the rectangle made by these points.

unsigned helper_max_of_four(const float& n1, const float& n2, const float& n3, const float& n4)
{
	float max_1 = (n1 < n2 ? n2 : n1);
	float max_2 = (n3 < n4 ? n4 : n3);
	return (max_1 < max_2 ? max_2 : max_1);
}

unsigned helper_min_of_four(const float& n1, const float& n2, const float& n3, const float& n4)
{
	float min_1 = (n1 < n2 ? n1 : n2);
	float min_2 = (n3 < n4 ? n3 : n4);
	return (min_1 < min_2 ? min_1 : min_2);
}

size_t find_area(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		size_t area;

		float arr[8];

		for (size_t i = 0; i < 8; i++)
		{
			fin >> arr[i];
		}

		fin.close();

		float max_y = helper_max_of_four(arr[1], arr[3], arr[5], arr[7]);
		float min_y = helper_min_of_four(arr[1], arr[3], arr[5], arr[7]);
		
		float max_x = helper_max_of_four(arr[0], arr[2], arr[4], arr[6]);
		float min_x = helper_min_of_four(arr[0], arr[2], arr[4], arr[6]);

		return (max_y - min_y) * (max_x - min_x);
	}

	std::cout << "\n\tCould not open file.txt!" << std::endl;
	return 0;
}

// Read symbol from the console and output the row and column number of all the places where it is present in a file.

void find_symbol(const char* path)
{
	char current_symbol;

	char symbol;
	std::cin.clear();
	std::cout << "\nEnter symbol: ";
	std::cin >> symbol;

	std::ifstream fin(path);

	if (fin)
	{
		size_t number_row = 1;
		size_t number_column = 1;

		for (; fin; ++number_column)
		{
			fin.read(&current_symbol, 1);

			if (fin)
			{
				if (current_symbol == symbol)
				{
					std::cout << "\nRow: " << number_row << "\t\tColumn: " << number_column << std::endl;
				}
				else if (current_symbol == '\n')
				{
					number_column = 0;
					number_row += 1;
				}
			}
		}

		fin.close();
		return;
	}

	std::cout << "\n\tCould not open file.txt!" << std::endl;
}

int main()
{
	const char* path = "file.txt";

	write_to_file(path);

	//std::ifstream fin(path);

	//std::cout << "\nNumber of rows in file.txt: " << number_rows(fin, path) << std::endl;

	//std::cout << "Size of file.txt: " << file_size(path) << std::endl;

	//std::cout << "Area: " << find_area(path) << std::endl;

	//find_symbol(path);

	return 0;
}