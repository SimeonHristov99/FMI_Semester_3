#include "helper_functions.h"
#include "Transaction_Array.h"
#include "Order_Array.h"

#include <iostream>
#include <fstream>
#include <ctime> // Source: https://stackoverflow.com/questions/4196153/find-how-many-seconds-past-since-1-1-1970

void Transaction_Array::Transaction::print() const
{
	std::cout << time_made << ' ' << senderId << ' ' << receiverId << ' ' << fmiCoins << '\n';
}

void Transaction_Array::resize()
{
	m_CAPACITY *= 2;

	Transaction* temp = new Transaction[m_CAPACITY];

	if (temp)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_transactions[i];
		}

		delete[] m_transactions;
		m_transactions = temp;
	}
	else
	{
		errors(ERRORS::NO_MEMORY);
	}	
}

void Transaction_Array::read()
{
	std::ifstream fin("transactions.dat", std::ios::binary | std::ios::app);

	if (!fin)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fin.seekg(0, std::ios::end);
		m_size = fin.tellg() / sizeof(Transaction);
		fin.close();

		if (m_size == 0)
		{
			m_CAPACITY = 8;
			m_transactions = new Transaction[m_CAPACITY];
			if(!m_transactions)
			{
				errors(ERRORS::NO_MEMORY);
			}
			return;
		}

		m_CAPACITY = m_size * 2;
		m_transactions = new Transaction[m_CAPACITY];

		if (!m_transactions)
		{
			errors(ERRORS::NO_MEMORY);
			return;
		}

		fin.open("transactions.dat", std::ios::binary);

		if (!fin.read(reinterpret_cast<char*>(m_transactions), (m_size * sizeof(Transaction))))
		{
			errors(ERRORS::NO_FILE);
		}

		fin.close();
	}
}

bool Transaction_Array::validate(const unsigned ID) const
{
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_transactions[i].senderId == UINT_MAX && m_transactions[i].receiverId == ID)
		{
			return false;
		}
	}

	return true;
}

Transaction_Array::Transaction_Array()
{
	read();
}

Transaction_Array::~Transaction_Array()
{
	delete[] m_transactions;
}

void Transaction_Array::write() const
{
	std::ofstream fout("transactions.dat", std::ios::binary | std::ios::trunc);

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		if (!fout.write(reinterpret_cast<const char*>(m_transactions), m_size * sizeof(Transaction)))
		{
			errors(ERRORS::NO_FILE);
		}

		fout.close();
	}
}

void Transaction_Array::print() const
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_transactions[i].print();
	}
}

bool Transaction_Array::add(const unsigned sID, const unsigned rID, const double coins)
{
	if (m_size == m_CAPACITY)
	{
		resize();
	}

	// If it is the system wallet, just add a transaction to the array.
	if (sID == UINT_MAX)
	{
		m_transactions[m_size++] = Transaction{ time(NULL), sID, rID, coins };
		return false;
	}

	// Validate the two IDs.
	if (validate(sID) != 0 || validate(rID) != 0)
	{
		errors(ERRORS::NO_ID);
		return true;
	}

	m_transactions[m_size++] = Transaction{ time(NULL), sID, rID, coins };

	return false;
}

double Transaction_Array::get_coins(const unsigned ID) const
{
	double result = 0;

	bool present = false;

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_transactions[i].senderId == ID)
		{
			result -= m_transactions[i].fmiCoins;
		}

		// Not else if because technically you can buy your own coins.
		if (m_transactions[i].receiverId == ID)
		{
			result += m_transactions[i].fmiCoins;

			present = true; // If it is present at least the system wallet would've given it coins.
		}
	}

	if (present == false)
	{
		errors(ERRORS::NO_ID);
		return -1;
	}

	return result;
}

size_t Transaction_Array::count_transactions(const unsigned ID) const
{
	size_t result = 0;

	bool present = false;
	bool first = false;
	bool last = false;

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_transactions[i].senderId == UINT_MAX && m_transactions[i].receiverId == ID)
		{
			present = true;
		}
		else if (m_transactions[i].senderId != UINT_MAX && (m_transactions[i].senderId == ID || m_transactions[i].receiverId == ID))
		{
			if (!first)
			{
				std::cout << m_transactions[i].time_made << ' ';

				first = true;
			}
			else if (!last)
			{
				std::cout << m_transactions[i].time_made << ' ';

				last = true;
			}

			++result;
		}		
	}

	if (present == false)
	{
		errors(ERRORS::NO_ID);
	}

	return result;
}