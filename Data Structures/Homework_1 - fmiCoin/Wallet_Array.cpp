#include "helper_functions.h"
#include "Wallet_Array.h"

#include <fstream>
#include <iostream>

void Wallet_Array::Wallet::print() const
{
	std::cout << id << " " << fiatMoney << " " << owner << '\n';
}

void Wallet_Array::copy(const Wallet_Array& rhs)
{
	if (rhs.m_wallets == nullptr)
	{
		errors(ERRORS::NULLPTR);
	}
	else
	{
		m_size = rhs.m_size;
		m_CAPACITY = m_size * 2;

		m_wallets = new Wallet[m_CAPACITY];

		for (size_t i = 0; i < m_size; i++)
		{
			m_wallets[i] = rhs.m_wallets[i];
		}
	}
}

void Wallet_Array::resize()
{
	m_CAPACITY *= 2;

	Wallet* temp = new Wallet[m_CAPACITY];

	if (temp)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_wallets[i];
		}

		delete[] m_wallets;
		m_wallets = temp;
	}
	else
	{
		errors(ERRORS::NO_MEMORY);
	}
}

void Wallet_Array::free_memory()
{
	delete[] m_wallets;
}

void Wallet_Array::read()
{
	std::ifstream fin("wallets.dat", std::ios::binary);

	if (!fin)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fin.seekg(0, std::ios::end);
		m_size = fin.tellg() / sizeof(Wallet);
		fin.close();

		// To provide speed, don't read, if there's nothing in the file.
		if (m_size == 0)
		{
			m_CAPACITY = 8;
			m_wallets = new Wallet[m_CAPACITY];
			if (!m_wallets)
			{
				errors(ERRORS::NO_MEMORY);
			}
			return;
		}

		m_CAPACITY = m_size * 2;

		m_wallets = new Wallet[m_CAPACITY];

		if (!m_wallets)
		{
			errors(ERRORS::NO_MEMORY);
			return;
		}

		fin.open("wallets.dat", std::ios::binary);
		
		if (!fin.read(reinterpret_cast<char*>(m_wallets), (m_size * sizeof(Wallet))))
		{
			errors(ERRORS::NO_FILE);
		}

		fin.close();
	}
}

bool Wallet_Array::validate_ID(const double id) const
{
	if (id > m_size || id == 0 || id == UINT_MAX)
	{
		errors(ERRORS::NO_ID);
		return true;
	}

	return false;
}

Wallet_Array::Wallet_Array()
{
	read();
}

Wallet_Array::Wallet_Array(const Wallet_Array& rhs)
{
	copy(rhs);
}

Wallet_Array& Wallet_Array::operator=(const Wallet_Array& rhs)
{
	if (this != &rhs)
	{
		free_memory();
		copy(rhs);
	}

	return *this;
}

Wallet_Array::~Wallet_Array()
{
	free_memory();
}

void Wallet_Array::write() const
{
	// Open the file for writing.
	std::ofstream fout("wallets.dat", std::ios::binary | std::ios::trunc);

	// Throw an error if there is a problem with the file.
	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		// Write the contents of the array. If there is a problem with the file, give an error.
		if (!fout.write(reinterpret_cast<const char*>(m_wallets), m_size * sizeof(Wallet)))
		{
			errors(ERRORS::NO_FILE);
		}

		// Close wallets.dat.
		fout.close();
	}
}

void Wallet_Array::print() const
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_wallets[i].print();
	}
}

void Wallet_Array::add(char* name, const double fiat, Transaction_Array& tarr)
{
	if (m_size == m_CAPACITY)
	{
		resize();
	}

	// Theoretically, it is possible to reach such a big size that the last available ID is UINT_MAX. If this is the case, stop creating wallets.
	if (m_size + 1 == UINT_MAX)
	{
		errors(ERRORS::MAX_WALLETS);
		return;
	}

	// Create a wallet and copy the values from the command to it.
	Wallet wallet;
	copy_char_arr(wallet.owner, name);
	wallet.id = m_size + 1;
	wallet.fiatMoney = fiat;

	// Add to the appropriate arrays.
	if (tarr.add(UINT_MAX, wallet.id, (fiat / EXCHANGE_RATE)) != 0)
	{
		return;
	}
	
	m_wallets[m_size++] = wallet;
}

bool Wallet_Array::wallet_info(const unsigned id, Transaction_Array& tarr) const
{
	if (validate_ID(id) != 0)
	{
		return true;
	}

	std::cout << "\tWallet " << id << ": " << m_wallets[id - 1].owner << ' ' << m_wallets[id - 1].fiatMoney << ' ' << tarr.get_coins(id) << "\n\n";

	return false;
}

bool Wallet_Array::set_fiat(const unsigned id, const double amount)
{
	if (validate_ID(id) != 0)
	{
		return true;
	}

	m_wallets[id - 1].fiatMoney += amount;

	return false;
}

bool Wallet_Array::print_owner(const unsigned id, std::ofstream& fout) const
{
	if (validate_ID(id) != 0)
	{
		return true;
	}

	fout << m_wallets[id - 1].owner;

	return false;
}

bool Wallet_Array::check_fiat(const unsigned id, const double coins)
{
	for (size_t i = 0; i < m_size; i++)
	{
		if (m_wallets[i].id == id)
		{
			if (coins > m_wallets[i].fiatMoney / EXCHANGE_RATE)
			{
				errors(ERRORS::NO_MONEY);
				return true;
			}

			return false;
		}
	}

	errors(ERRORS::NO_ID);
	return true;
}

void Wallet_Array::swap(Wallet& w1, Wallet& w2)
{
	Wallet temp = w1;
	w1 = w2;
	w2 = temp;
}

bool Wallet_Array::sort(Transaction_Array& tarr)
{
	for (size_t i = 0; i < m_size - 1; i++)
	{
		size_t maxIndex = i;

		for (size_t j = i + 1; j < m_size; j++)
		{
			if (tarr.get_coins(m_wallets[j].id) > tarr.get_coins(m_wallets[maxIndex].id))
			{
				maxIndex = j;
			}
		}

		swap(m_wallets[i], m_wallets[maxIndex]);
	}

	return false;
}

bool Wallet_Array::attract_investors(Transaction_Array& tarr)
{
	if (sort(tarr) != 0)
	{
		return true;
	}

	for (size_t i = 0; i < m_size; i++)
	{
		std::cout << "\tPosition " << i + 1 << ": ";
		std::cout << tarr.get_coins(m_wallets[i].id) << ' ';
		std::cout << tarr.count_transactions(m_wallets[i].id);
		std::cout << std::endl;
	}

	return false;
}