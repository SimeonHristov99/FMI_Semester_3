#include <iostream>
#include <fstream>
#include "helper_functions.h"

STATUS decompress(const char* input, const char* output)
{
	// Open input file for reading.
	std::ifstream fin(input);
	if (!fin)
	{
		return STATUS::NO_INPUT;
	}

	// Get the size of the input string and form a character array.
	fin.seekg(0, std::ios::end);
	size_t size_file = fin.tellg();
	char* buffer = new char[size_file + 1];
	size_t index_buffer = 0;

	fin.seekg(0, std::ios::beg);

	// Copy the contents of the file into the char*.
	while (fin)
	{
		char c;
		fin.read(&c, 1);
		if (fin)
		{
			buffer[index_buffer++] = c;
		}
	}
	fin.close();
	buffer[index_buffer] = { '\0' };

	Stack<unsigned> numbers;
	Stack<unsigned> file_indexes;
	file_indexes.push(1);

	bool in_quotation_marks = false;
	char current_file[1024];

	generate_file_name(file_indexes.top() - 1, current_file);

	std::ofstream fout(current_file);
	if (!fout)
	{
		delete[] buffer;
		return STATUS::NO_OUTPUT;
	}

	for (const char* c = buffer; *c; ++c)
	{
		if (!in_quotation_marks && is_digit(*c))
		{
			fout.close();
			
			generate_file_name(file_indexes.top(), current_file);

			fout.open(current_file);

			file_indexes.push(file_indexes.top() + 1);

			if (*c == '0')
			{
				delete[] buffer;
				return STATUS::REPEAT_ZERO_TIMES;
			}

			unsigned number = 0;
			do
			{
				number = number * 10 + (*c - '0');
				++c;
			} while (is_digit(*c));

			numbers.push(number);

			if (*c != '(')
			{
				delete[] buffer;
				return STATUS::NO_SYMBOL;
			}
		}
		else if (!in_quotation_marks && *c == ')')
		{
			unsigned to_repeat = numbers.top();
			numbers.pop();
			file_indexes.pop();

			// Append the current fout buffer to_repeat times to the file that has a name with the previous index.
			fout.close();

			std::ifstream fin(current_file);
			if (!fin)
			{
				delete[] buffer;
				return STATUS::FILE_CORRUPT;
			}

			char copy_name[1024] = { '\0' };
			size_t i = 0;
			for (const char* c = current_file; *c; ++c, ++i)
			{
				copy_name[i] = *c;
			}

			generate_file_name(file_indexes.top() - 1, current_file);

			fout.open(current_file, std::ios::app);
			if (!fout)
			{
				delete[] buffer;
				return STATUS::FILE_CORRUPT;
			}

			std::filebuf* to_copy = fin.rdbuf();

			for (size_t i = 0; i < to_repeat; i++)
			{
				fout << to_copy;
				fin.seekg(0);
				to_copy = fin.rdbuf();
			}

			fout.close();
			fin.close();
			remove(copy_name);
		}
		else if (!in_quotation_marks && *c == '(')
		{
			delete[] buffer;
			return STATUS::INCORRECT_BRAKETS;
		}
		else if (*c == '"')
		{
			in_quotation_marks = (in_quotation_marks ? false : true);
		}
		else if (*c == '\\')
		{
			if (in_quotation_marks)
			{
				if (!(fout << *c))
				{
					delete[] buffer;
					return STATUS::FILE_CORRUPT;
				}
			}

			if (!*(c + 1))
			{
				delete[] buffer;
				return STATUS::NO_SYMBOL;
			}

			if (!(fout << *(++c)))
			{
				delete[] buffer;
				return STATUS::FILE_CORRUPT;
			}
		}
		else
		{
			// Writes directly in the output file.
			if (!(fout << *c))
			{
				delete[] buffer;
				return STATUS::FILE_CORRUPT;
			}
		}
	}

	fout.close();

	delete[] buffer;

	remove(output);
	rename("1.txt", output);

	return STATUS::SUCCESS;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "\n\t\tERROR: The program requires two arguments!\n";
		return -1;
	}

	switch (decompress(argv[1], argv[2]))
	{
	case STATUS::NO_INPUT:
	{
		std::cout << "\n\t\tERROR: The file containing the string does not exist or could not be opened!\n";
		return -1;
	}
	case STATUS::NO_OUTPUT:
	{
		std::cout << "\n\t\tERROR: The file for the output could not be opened!\n";
		return -1;
	}
	case STATUS::FILE_CORRUPT:
	{
		std::cout << "\n\t\tERROR: File is corrupt! Please try again later!\n";
		return -1;
	}
	case STATUS::REPEAT_ZERO_TIMES:
	{
		std::cout << "\n\t\tERROR: An expression cannot be repeated zero times!\n";
		return -1;
	}
	case STATUS::NO_NUMBER:
	{
		std::cout << "\n\t\tERROR: The number indicating how many times the expression should be repeated was not found!\n";
		return -1;
	}
	case STATUS::INCORRECT_BRAKETS:
	{
		std::cout << "\n\t\tERROR: Incorrect braket(s) detected!\n";
		return -1;
	}
	case STATUS::INCORRECT_QMARKS:
	{
		std::cout << "\n\t\tERROR: Incorrect quotation marks detected!\n";
		return -1;
	}
	case STATUS::NO_SYMBOL:
	{
		std::cout << "\n\t\tERROR: The symbol after '\\' was not found!\n";
		return -1;
	}
	default:
	{
		std::cout << "String decompressed sucessfully.\n";
		return 0;
	}
	}

	return -1;
}