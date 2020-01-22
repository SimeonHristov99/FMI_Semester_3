#pragma once

#include <vector>

class Permutation_Generator
{
private:
	size_t m_size;
	std::vector<unsigned> m_base;

public:
	Permutation_Generator(size_t n);

	const std::vector<unsigned>& current() const;

	std::vector<unsigned> operator()();

	void print() const;
};