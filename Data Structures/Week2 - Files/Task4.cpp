#include "pch.h"
#include <iostream>
#include <fstream>

void count(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		size_t count_lines = 1;
		size_t count_words = 0;
		size_t count_symbols = 0;

		char c;

		bool in_word = false;

		while (fin)
		{
			fin.read(&c, 1);
			if (fin)
			{
				if (c == '\n')
				{
					++count_lines;
					++count_symbols;
					in_word = false;
				}
				else if (in_word == false && c != '\t' && c != ' ')
				{
					++count_words;
					in_word = true;
				}
				else if (c == ' ')
				{
					in_word = false;
				}
				else if (c == '\t')
				{
					++count_symbols;
					in_word = false;
				}

				++count_symbols;
			}			
		}

		std::cout << "Number of symbols: " << count_symbols << "\nNumber of words: " << count_words << "\nNumber of new lines: " << count_lines << std::endl;
	}

	fin.close();
}

int main()
{
	const char* path = "C:/Users/Work/Desktop/Week2/input.txt";

	count(path);

	return 0;
}