#include "helper_functions.h"

unsigned abs_diff(const unsigned n1, const unsigned n2)
{
	return n1 > n2 ? n1 - n2 : n2 - n1;
}

size_t to_number(std::string str)
{
	size_t number = 0;

	while (!str.empty())
	{
		number = number * 10 + (str[str.size() - 1] - '0');

		str.pop_back();
	}

	return number;
}
