#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

void print_file(const char* path)
{
	std::ifstream fin(path);

	if (fin)
	{
		unsigned faculty_number;
		char name[256];
		float grade;
		while (fin >> name >> faculty_number >> grade)
		{
			std::cout << name << " " << faculty_number << " " << grade << std::endl;
		}
	}
}

int main()
{
	const char* path = "C:/Users/Work/Desktop/Week2/students.txt";

	print_file(path);

	return 0;
}