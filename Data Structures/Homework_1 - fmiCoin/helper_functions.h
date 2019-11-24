#pragma once

#define BUFFER_FOR_TEXT_FILE 100 // Can be changed if necessary. Used for the name of the text file, generated for every approved order.

// All types of errors the program outputs.
enum class ERRORS
{
	NULLPTR,
	NO_MEMORY,

	SELLING_MORE,

	MAX_WALLETS,
	MAX_NAME,

	NO_FILE,
	NO_RENAME,
	NO_ID,
	NO_COINS,
	NO_MONEY,

	INCORRECT_COMMAND,
	INCORRECT_VALUE,

	SYNTAX_ADD_WALLET,
	SYNTAX_TRANSFER,
	SYNTAX_ORDER,
	SYNTAX_WALLET_INFO,
};

// Return the length of a character array.
size_t get_length(const char* c);

// Copy contents of rhs character array to lhs character array.
void copy_char_arr(char* lhs, const char* rhs);

// Return whether two character arrays are equal.
bool are_equal(const char* rhs, const char* lhs);

// Return whether a character is a digit.
bool is_digit(const char c);

// Return whether a character is a letter.
bool is_letter(const char c);

// Based on the enumerated value output the appropriate error.
void errors(const ERRORS& err);

// Return the power of ten.
unsigned power_10(const size_t power);

// Open wallets.dat, transactions.dat and orders.dat with an ofstream object without modifying contents to make sure they exist.
void validate_files();

// Get the information needed to create a wallet from the buffer.
bool get_info_add_wallet(const char* buffer, size_t& index, double& fiat, char* name);

// Get fmiCoins from the buffer. Works with whole numbers as well as fractions.
bool coins_from_buffer(double& coins, const char* buffer, size_t index);

// Get the information needed to create a transfer from the buffer.
bool get_info_transfer(const char* buffer, size_t& index, unsigned& sender, unsigned& receiver, double& coins);

// Get the ID from the buffer.
bool get_info_wallet_info(const char* buffer, size_t& index, unsigned& id);

// Get the information needed to create an order from the buffer.
bool get_info_order(const char* buffer, size_t& index, char* sub_buffer_2, char* sub_buffer_3, double& coins, unsigned& id);