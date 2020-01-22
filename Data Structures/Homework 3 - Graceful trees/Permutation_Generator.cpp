#include <iostream>
#include "Permutation_Generator.h"

Permutation_Generator::Permutation_Generator(size_t n)
	: m_size(n)
{
	for (size_t j = 0, i = 1; j < n; ++j, i += 2)
	{
		if (i % 2 == 1)
		{
			m_base.push_back(i);
		}
	}
}

const std::vector<unsigned>& Permutation_Generator::current() const
{
	return m_base;
}

std::vector<unsigned> Permutation_Generator::operator()()
{
	if (m_base.size() < 2)
	{
		return {};
	}

	std::vector<unsigned>::iterator decrease = m_base.end() - 2;

	while (*decrease > *(decrease + 1) && decrease >= m_base.begin())
	{
		if (decrease == m_base.begin())
		{
			return {};
		}

		--decrease;
	}

	std::vector<unsigned>::iterator larger = m_base.end() - 1;

	while (*larger < *decrease)
	{
		--larger;
	}

	std::swap(*larger, *decrease);

	std::vector<unsigned>::iterator right = m_base.end() - 1;
	std::vector<unsigned>::iterator left = decrease + 1;

	while (left < right)
	{
		std::swap(*left, *right);
		++left;
		--right;
	}

	return m_base;
}

void Permutation_Generator::print() const
{
	for (auto a : m_base)
	{
		std::cout << a << ' ';
	}
}
