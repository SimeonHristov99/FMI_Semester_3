#include <iostream>
#include <fstream>

std::streamoff getSize(const char* path)
{
	std::ifstream in(path);

	if (in)
	{
		in.seekg(0, std::ios::end);
		return in.tellg();
	}

	std::cout << "\n\n\t\tERROR: Could not open \"" << path << "\"!" << std::endl;
	return -1;
}

int main()
{
	std::cout << "Current size of file is " << getSize("file.txt") << "." << std::endl;

	std::cout << "\nWriting 26 bytes (i.e. symbols) ---------------------------------------------------------------------\n" << std::endl;

	std::ofstream out("file.txt", std::fstream::trunc);

	for (char i = 'a'; i <= 'z'; i++)
	{
		out << i;
	}

	out.close();

	std::cout << "\tSize is now " << getSize("file.txt") << "." << std::endl;

	std::cout << "\n\nDeleting everything ---------------------------------------------------------------------\n" << std::endl;

	out.open("file.txt", std::fstream::trunc);
	std::cout << "\tSize is now " << getSize("file.txt") << "." << std::endl;

	out.close();

	return 0;
}