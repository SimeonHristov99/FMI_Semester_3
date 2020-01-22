#pragma once

#include <string>

unsigned abs_diff(const unsigned n1, const unsigned n2);

size_t to_number(std::string str);

template <class T>
T max(const T& arg1, const T& arg2);

template<class T>
inline T max(const T& arg1, const T& arg2)
{
	return arg1 > arg2 ? arg1 : arg2;
}
