#include "pch.h"
#include <iostream>
#include <fstream>

void printFile(const char* path)
{
	std::ifstream in(path);

	if (in)
	{
		char line[256]; // One line has to be <= 255 symbols (bytes).
		while (in)
		{
			in.getline(line, 256); // One line has to be <= 255 symbols (bytes).
			std::cout << line << std::endl;
		}
	}
	else
	{
		std::cout << "\n\tCould not open file!" << std::endl;
	}
}

int main()
{
	std::ofstream fout("C:/Users/Work/Desktop/Week2/students.txt");

	if (fout)
	{
		int facultyNumber;
		char name[128]; // Has to be <= 127 symbols (bytes). Has to be one name (ex. first).
		float grade;

		while (std::cin >> name >> facultyNumber >> grade)
		{
			fout << name << " " << facultyNumber << " " << grade << std::endl;
		}
	}

	else
	{
		std::cout << "\n\n\t\tERROR: Could not open file!" << std::endl;
	}

	fout.close();

	std::cout << "\n\n\tCurrent content of students.txt" << std::endl;
	printFile("C:/Users/Work/Desktop/Week2/students.txt");

	std::cout << "\nDeleting content." << std::endl;
	fout.open("C:/Users/Work/Desktop/Week2/students.txt", std::fstream::trunc);
	fout.close();

	return 0;
}