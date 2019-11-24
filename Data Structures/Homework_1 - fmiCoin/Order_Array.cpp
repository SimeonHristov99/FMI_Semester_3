#include "helper_functions.h"
#include "Order_Array.h"

#include <fstream>
#include <iostream>
#include <ctime>

void Order_Array::Order::print() const
{
	std::cout << walletId << ' ' << (type == Type::SELL ? "SELL" : "BUY") << ' ' << fmiCoins << "\n\n";
}

void Order_Array::resize()
{
	m_CAPACITY *= 2;

	Order* temp = new Order[m_CAPACITY];

	if (temp)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_orders[i];
		}

		delete[] m_orders;
		m_orders = temp;
	}
	else
	{
		errors(ERRORS::NO_MEMORY);
	}	
}

void Order_Array::read()
{
	std::ifstream fin("orders.dat", std::ios::binary | std::ios::app);

	if (!fin)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fin.seekg(0, std::ios::end);
		m_size = fin.tellg() / sizeof(Order);
		fin.close();

		if (m_size == 0)
		{
			m_CAPACITY = 8;
			m_orders = new Order[m_CAPACITY];
			if (!m_orders)
			{
				errors(ERRORS::NO_MEMORY);
			}
			return;
		}

		m_CAPACITY = m_size * 2;
		m_orders = new Order[m_CAPACITY];

		if (!m_orders)
		{
			errors(ERRORS::NO_MEMORY);
			return;
		}

		fin.open("orders.dat", std::ios::binary);

		if (!fin.read(reinterpret_cast<char*>(m_orders), m_size * sizeof(Order)))
		{
			errors(ERRORS::NO_FILE);
		}

		fin.close();
	}
}

bool Order_Array::make_sell(Order& seller, Order& buyer, double& total_coins, double& coins, Wallet_Array& warr, Transaction_Array& tarr)
{
	// for less coins:
	if (buyer.fmiCoins < seller.fmiCoins)
	{
		// Add a transaction.
		if (tarr.add(seller.walletId, buyer.walletId, buyer.fmiCoins) != 0)
		{
			return true;
		}

		// Change fiatMoney of the buyer.
		if (warr.set_fiat(buyer.walletId, buyer.fmiCoins * EXCHANGE_RATE * (-1)) != 0)
		{
			return true;
		}

		// Change fiatMoney of the seller.
		if (warr.set_fiat(seller.walletId, buyer.fmiCoins * EXCHANGE_RATE) != 0)
		{
			return true;
		}

		// Add coins.
		total_coins += buyer.fmiCoins;

		// Change the coins which are going to be written.
		coins = buyer.fmiCoins;

		// Change the coins in the offer.
		seller.fmiCoins -= buyer.fmiCoins;

		// Delete the BUY order.
		buyer.fmiCoins = 0;

		return false;
	}

	// for more coins:
	if (buyer.fmiCoins > seller.fmiCoins)
	{
		if (tarr.add(seller.walletId, buyer.walletId, seller.fmiCoins) != 0)
		{
			return true;
		}

		if (warr.set_fiat(buyer.walletId, seller.fmiCoins * EXCHANGE_RATE * (-1)) != 0)
		{
			return true;
		}

		if (warr.set_fiat(seller.walletId, seller.fmiCoins * EXCHANGE_RATE) != 0)
		{
			return true;
		}

		total_coins += seller.fmiCoins;

		coins = seller.fmiCoins;

		// Rewrite the BUY order to be for less amount of fmiCoins.
		buyer.fmiCoins -= seller.fmiCoins;

		seller.fmiCoins = 0;

		return false;
	}

	// for eq coins:
	if (tarr.add(seller.walletId, buyer.walletId, buyer.fmiCoins) != 0)
	{
		return true;
	}

	if (warr.set_fiat(buyer.walletId, buyer.fmiCoins * EXCHANGE_RATE * (-1)) != 0)
	{
		return true;
	}

	if (warr.set_fiat(seller.walletId, buyer.fmiCoins * EXCHANGE_RATE) != 0)
	{
		return true;
	}

	total_coins += buyer.fmiCoins;

	coins = buyer.fmiCoins;

	buyer.fmiCoins = 0;

	seller.fmiCoins = 0;

	return false;
}

bool Order_Array::rename_file(unsigned id)
{
	char sub_buffer_4[128];

	size_t digits = 0;

	// Count the number of digits.
	size_t temp = id;

	while (temp)
	{
		temp /= 10;

		++digits;
	}

	sub_buffer_4[digits] = ' ';

	size_t copy_digits = digits;

	while (id)
	{
		sub_buffer_4[digits-- - 1] = id % 10 + '0';

		id /= 10;
	}

	size_t time_made = time(NULL);

	size_t digits_time = 0;

	size_t temp_time = time_made;

	while (temp_time)
	{
		++digits_time;

		temp_time /= 10;
	}

	// Start from the back of time_made and the array.
	size_t end = copy_digits + digits_time + 1;

	// Put a term 0 at end of buffer.
	sub_buffer_4[end] = '.';
	sub_buffer_4[end + 1] = 't';
	sub_buffer_4[end + 2] = 'x';
	sub_buffer_4[end + 3] = 't';
	sub_buffer_4[end + 4] = '\0';

	while (time_made)
	{
		sub_buffer_4[--end] = time_made % 10 + '0';

		time_made /= 10;
	}

	if (rename("to_be_renamed.txt", sub_buffer_4) != 0)
	{
		errors(ERRORS::NO_RENAME);
		return true;
	}

	return false;
}

bool Order_Array::edit_text_file(bool delete_file, std::ofstream& fout, const Order& order, const size_t number_transfers, const double total_coins)
{
	// If there are no buyers, delete the file and add the order to the array.
	if (delete_file)
	{
		fout.close();

		remove("to_be_renamed.txt");

		m_orders[m_size++] = order;

		return false;
	}

	// If there buyers but not enough to complete the order, add the leftover to the array and keep the file.
	if (order.fmiCoins > 0)
	{
		m_orders[m_size++] = order;
	}

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
		return true;
	}

	fout << "\n\n\t Number of transfers: " << number_transfers << "\n Value of exchanged fmiCoins: " << total_coins * EXCHANGE_RATE;

	fout.close();

	if (rename_file(order.walletId) != 0)
	{
		return true;
	}

	return false;
}

Order_Array::Order_Array()
{
	read();
}

Order_Array::~Order_Array()
{
	delete[] m_orders;
}

void Order_Array::write() const
{
	std::ofstream fout("orders.dat", std::ios::binary | std::ios::trunc);

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		for (size_t i = 0; i < m_size; i++)
		{
			// If no fmiCoins are offered then the order has been deleted.
			if (m_orders[i].fmiCoins != 0)
			{
				if (!fout.write(reinterpret_cast<const char*>(&m_orders[i]), sizeof(Order)))
				{
					errors(ERRORS::NO_FILE);
				}
			}
		}

		fout.close();
	}
}

void Order_Array::print() const
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_orders[i].print();
	}
}

double Order_Array::coins_for_sell(const unsigned ID) const
{
	double result = 0;

	for (size_t i = 0; i < m_size; i++)
	{
		if (m_orders[i].type == Order::Type::SELL && m_orders[i].walletId == ID)
		{
			// Does not matter whether the offer was deleted. Then it would be + 0.
			result += m_orders[i].fmiCoins;
		}
	}

	return result;
}

bool Order_Array::sell(const unsigned id, double& coins, double& total_coins, size_t& number_transfers, Wallet_Array& warr, Transaction_Array& tarr)
{
	// Open a text file for writing.
	std::ofstream fout("to_be_renamed.txt", std::ios::app);

	// Instantiate the sell order.
	Order seller = { Order::Type::SELL, id, coins };

	// Marks whether the file should be deleted.
	bool delete_file = true;

	// Go through the array of orders.					
	for (size_t i = 0; i < m_size && seller.fmiCoins > 0; i++)
	{
		// Skip the SELL offers.
		if (m_orders[i].type == Order::Type::BUY)
		{
			// Approve the order.
			if (make_sell(seller, m_orders[i], total_coins, coins, warr, tarr))
			{
				return true;
			}

			if (!fout)
			{
				errors(ERRORS::NO_FILE);
				return true;
			}

			// Print the receiver of the coins.
			if (warr.print_owner(seller.walletId, fout))
			{
				return true;
			}

			// Print a space.
			if (!(fout << ' '))
			{
				errors(ERRORS::NO_FILE);
				return true;
			}

			// Print the sender.
			if (warr.print_owner(m_orders[i].walletId, fout))
			{
				return true;
			}

			// Print the coins and a new line.
			if (!(fout << ' ' << coins << '\n'))
			{
				errors(ERRORS::NO_FILE);
			}

			// Increment the counter.
			++number_transfers;

			// The file should be deleted only when there weren't any buys made.
			delete_file = false;
		}
	}

	if (edit_text_file(delete_file, fout, seller, number_transfers, total_coins) != 0)
	{
		return true;
	}

	return false;
}

bool Order_Array::buy(const unsigned id, double& coins, double& total_coins, size_t& number_transfers, Wallet_Array& warr, Transaction_Array& tarr)
{
	std::ofstream fout("to_be_renamed.txt", std::ios::app);

	Order buyer = { Order::Type::BUY, id, coins };

	bool delete_file = true;

	for (size_t i = 0; i < m_size && buyer.fmiCoins > 0; i++)
	{
		if (m_orders[i].type == Order::Type::SELL && m_orders[i].fmiCoins != 0)
		{
			if (make_sell(m_orders[i], buyer, total_coins, coins, warr, tarr) != 0)
			{
				return true;
			}

			if (!fout)
			{
				errors(ERRORS::NO_FILE);
			}
			else
			{
				if (warr.print_owner(buyer.walletId, fout) != 0)
				{
					return true;
				}

				if (!(fout << ' '))
				{
					errors(ERRORS::NO_FILE);
				}

				if (warr.print_owner(m_orders[i].walletId, fout) != 0)
				{
					return true;
				}

				if (!(fout << ' ' << coins << '\n'))
				{
					errors(ERRORS::NO_FILE);
				}
			}

			++number_transfers;

			delete_file = false;
		}
	}

	if (edit_text_file(delete_file, fout, buyer, number_transfers, total_coins) != 0)
	{
		return true;
	}

	return false;
}