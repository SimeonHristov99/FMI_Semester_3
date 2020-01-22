#pragma once

#include "Wallet_Array.h"
#include "Transaction_Array.h"

class Order_Array
{
private:
	struct Order
	{
		enum class Type // Source: https://stackoverflow.com/questions/18335861/why-is-enum-class-preferred-over-plain-enum
		{
			SELL,
			BUY,
		} type;
		unsigned walletId;
		double fmiCoins;

		// Prints normally in console.
		void print() const;
	} *m_orders;

	size_t m_size;
	size_t m_CAPACITY;

	void resize();

	void read();

	bool make_sell(Order& seller, Order& buyer, double& total_coins, double& coins, Wallet_Array& warr, Transaction_Array& tarr);

	bool rename_file(unsigned id);

	bool edit_text_file(bool delete_file, std::ofstream& fout, const Order& order, const size_t number_transfers, const double total_coins);

public:
	Order_Array();

	Order_Array(Order_Array& rhs) = delete;
	Order_Array& operator=(Order_Array& rhs) = delete;

	~Order_Array();

	void write() const;

	void print() const;

	double coins_for_sell(const unsigned ID) const;

	bool sell(const unsigned id, double& coins, double& total_coins, size_t& number_transfers, Wallet_Array& warr, Transaction_Array& tarr);

	bool buy(const unsigned id, double& coins, double& total_coins, size_t& number_transfers, Wallet_Array& warr, Transaction_Array& tarr);
};