#pragma once

#define SIZE_NAME 256 // Maximum size of name.

#include "Transaction_Array.h"

#include <fstream>

class Wallet_Array
{
private:
	struct Wallet
	{
		unsigned id;
		double fiatMoney;
		char owner[SIZE_NAME] = { '\0' };

		// Prints normally in console.
		void print() const;
	} *m_wallets;

	// Indicates current size.
	size_t m_size;
	// Indicates max size. If reached, will resize.
	size_t m_CAPACITY;

	// Copies contents of one wallet array to another. Used in copy constructor and operator =.
	void copy(const Wallet_Array& rhs);

	// Resizes the array with a coefficient of 2.
	void resize();

	// Frees up the dynamically allocated m_wallets.
	void free_memory();

	// Opens the wallets.dat and puts the contents in m_wallets.
	void read();

	bool validate_ID(const double id) const;

	// Swaps two wallets.
	void swap(Wallet& w1, Wallet& w2);

	// Sorts m_wallets according to fmiCoins.
	bool sort(Transaction_Array& tarr);

public:
	// Creates an empty array with max size 8. Uses read to get the wallets from wallets.dat.
	Wallet_Array();

	// Copying needed for attract-investors().
	Wallet_Array(const Wallet_Array& rhs);
	Wallet_Array& operator=(const Wallet_Array& rhs);

	~Wallet_Array();

	void write() const;

	void print() const;
	
	// Adds a wallet and makes a transaction.
	void add(char* name, const double fiat, Transaction_Array& tarr);

	bool wallet_info(const unsigned id, Transaction_Array & tarr) const;

	// Change fiatMoney. The boolean indicates whether to add or subtract.
	bool set_fiat(const unsigned id, const double amount);

	// Print the owner of a wallet.
	bool print_owner(const unsigned id, std::ofstream& fout) const;

	// Returns whether ID has enough fiatMoney to buy given amount of fmiCoins.
	bool check_fiat(const unsigned id, const double coins);

	bool attract_investors(Transaction_Array& tarr);
};