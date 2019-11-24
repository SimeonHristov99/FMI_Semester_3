#pragma once

#define EXCHANGE_RATE 375 // Constant exchange rate.

class Transaction_Array
{
private:
	struct Transaction
	{
		long long time_made;
		unsigned senderId;
		unsigned receiverId;
		double fmiCoins;

		void print() const;
	} *m_transactions;

	size_t m_size;
	size_t m_CAPACITY;

	void resize();

	void read();

	bool validate(const unsigned ID) const;

public:
	// Creates an empty array with max size 8. Uses read to get the transactions from transactions.dat.
	Transaction_Array();

	// Copying is not needed.
	Transaction_Array(const Transaction_Array& rhs) = delete;
	Transaction_Array& operator=(const Transaction_Array& rhs) = delete;

	~Transaction_Array();

	void write() const;

	void print() const;

	// Add a transaction after validating the IDs.
	bool add(const unsigned sID, const unsigned rID, const double coins);

	// Return how many coins an ID currently has. If the ID is not present in the file, it is invalid.
	double get_coins(const unsigned ID) const;

	size_t count_transactions(const unsigned ID) const;
};