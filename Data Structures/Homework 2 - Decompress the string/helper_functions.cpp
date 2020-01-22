#include <fstream>
#include "helper_functions.h"

bool is_digit(const char c)
{
	return c >= '0' && c <= '9';
}

STATUS to_output(const char* to, Stack<char>& letters)
{
	std::ofstream fout(to);
	if (!fout)
	{
		return STATUS::NO_OUTPUT;
	}

	if (letters.print(fout) != 0)
	{
		return STATUS::FILE_CORRUPT;
	}

	return STATUS::SUCCESS;
}

void generate_file_name(unsigned index, char* buffer)
{
	index += 1;

	int number_digits = 0;
	unsigned index_copy = index;
	while (index_copy)
	{
		++number_digits;
		index_copy /= 10;
	}

	buffer[number_digits] = '.';
	buffer[number_digits + 1] = 't';
	buffer[number_digits + 2] = 'x';
	buffer[number_digits + 3] = 't';
	buffer[number_digits + 4] = '\0';

	for (;number_digits; --number_digits)
	{
		buffer[number_digits - 1] = index % 10 + '0';
	}
}
