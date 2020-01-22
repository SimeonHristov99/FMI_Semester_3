#include "helper_functions.h"
#include <iostream>
#include <fstream>

size_t get_length(const char* c)
{
	size_t i = 0;

	for (; c[i]; ++i) {	}

	return i;
}

void copy_char_arr(char* lhs, const char* rhs)
{
	size_t i = 0;

	for (; rhs[i]; i++)
	{
		lhs[i] = rhs[i];
	}

	lhs[i] = '\0';
}

bool are_equal(const char* rhs, const char* lhs)
{
	if (get_length(rhs) != get_length(lhs))
	{
		return false;
	}

	for (size_t i = 0; lhs[i] != '\0'; i++)
	{
		if (rhs[i] != lhs[i])
		{
			return false;
		}
	}

	return true;
}

unsigned power_10(const size_t power)
{
	unsigned result = 1;

	for (size_t i = 0; i < power; i++)
	{
		result *= 10;
	}

	return result;
}

bool is_digit(const char c)
{
	return c >= '0' && c <= '9';
}

bool is_letter(const char c)
{
	return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

void errors(const ERRORS& err)
{
	switch (err)
	{
	case ERRORS::NULLPTR:
	{
		std::cerr << "\n\t\tCRITICAL ERROR: Null pointer detected!\n\n";
		break;
	}
	case ERRORS::NO_MEMORY:
	{
		std::cerr << "\n\t\tCRITICAL ERROR: Not enough memory!\n\n";
		break;
	}
	case ERRORS::MAX_WALLETS:
	{
		std::cerr << "\n\t\tCRITICAL ERROR: Reached maximum number of wallets! The program will not create any more wallets!\n\n";
		break;
	}
	case ERRORS::NO_FILE:
	{
		std::cerr << "\n\tCRITICAL ERROR: File is corrupt!" << std::endl;
		break;
	}
	case ERRORS::INCORRECT_COMMAND:
	{
		std::cerr << "\n\t\tERROR: No such command is present! Please try again!\n\n";
		break;
	}
	case ERRORS::SYNTAX_ADD_WALLET:
	{
		std::cerr << "\n\t\tNOTE: Syntax is \"add-wallet **fiatMoney** **name**\". Please try again!\n\n";
		break;
	}
	case ERRORS::MAX_NAME:
	{
		std::cerr << "\n\t\tERROR: Name exceeds the limit of 255 letters! Please try again!\n\n";
		break;
	}
	case ERRORS::SYNTAX_TRANSFER:
	{
		std::cerr << "\n\t\tNOTE: Syntax is \"transfer **senderId** **receiverId** **fmiCoins**\". Please try again!\n\n";
		break;
	}
	case ERRORS::NO_ID:
	{
		std::cerr << "\n\t\tERROR: ID not found! Please try again!\n\n";
		break;
	}
	case ERRORS::NO_COINS:
	{
		std::cerr << "\n\t\tERROR: The sender does not have the stated amount of fmiCoins! Please try again\n\n";
		break;
	}
	case ERRORS::SYNTAX_WALLET_INFO:
	{
		std::cerr << "\n\t\tNOTE: Syntax is \"wallet-info **walletId**\". Please try again!\n\n";
		break;
	}
	case ERRORS::INCORRECT_VALUE:
	{
		std::cerr << "\n\t\tERROR: Incorrect value detected! Please try again!\n\n";
		break;
	}
	case ERRORS::SYNTAX_ORDER:
	{
		std::cerr << "\n\t\tNOTE: Syntax is \"make-order **type** **fmiCoins** **walletId**\". Please try again!\n\n";
		break;
	}
	case ERRORS::NO_RENAME:
	{
		std::cerr << "\n\t\tERROR: Could not rename file!\n\n";
		break;
	}
	case ERRORS::SELLING_MORE:
	{
		std::cerr << "\n\t\tERROR: Sender ID has a sale for more than he is currently transferring! Please try again!\n\n";
		break;
	}
	case ERRORS::NO_MONEY:
	{
		std::cerr << "\n\t\tERROR: ID does not have enough fiatMoney! Please try again!\n\n";
		break;
	}
	}
}

void validate_files()
{
	std::ofstream fout("wallets.dat", std::ios::app | std::ios::binary);

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fout.close();
	}

	fout.open("transactions.dat", std::ios::app | std::ios::binary);

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fout.close();
	}

	fout.open("orders.dat", std::ios::app | std::ios::binary);

	if (!fout)
	{
		errors(ERRORS::NO_FILE);
	}
	else
	{
		fout.close();
	}
}

bool get_info_add_wallet(const char* buffer, size_t& index, double& fiat, char* name)
{
	// Make sure there is a space between the name of the command and the money.
	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_ADD_WALLET);
		return true;
	}

	// Skip it.
	++index;

	// 1. Cannot be a negative number. 2. At least one digit expected.
	if (!(is_digit(buffer[index])))
	{
		errors(ERRORS::SYNTAX_ADD_WALLET);
		return true;
	}

	for (; is_digit(buffer[index]); ++index)
	{
		fiat = fiat * 10 + (buffer[index] - '0');
	}

	// Make sure there is a space between the name of the command and the money.
	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_ADD_WALLET);
		return true;
	}

	// Skip it.
	++index;

	// At least one character expected.
	if (!(is_letter(buffer[index])))
	{
		errors(ERRORS::SYNTAX_ADD_WALLET);
		return true;
	}

	// Get the name from the buffer.
	for (size_t j = 0; buffer[index] != '\0'; ++index, ++j)
	{
		name[j] = buffer[index];
	}

	// Name has to be shorder than 256.
	if (get_length(name) > 255)
	{
		errors(ERRORS::MAX_NAME);
		return true;
	}

	return false;
}

bool coins_from_buffer(double& coins, const char* buffer, size_t index)
{
	size_t j = 0; // Used to calculate the power of 10 in case fmiCoins is a fraction.

	// Used to make sure there are no more than one ".".
	bool flag = false;

	for (; buffer[index] != '\0'; ++index)
	{
		if (buffer[index] == '.') // Use the "." that is part of the Num Lock section.
		{
			// Will be true only if the number has more than one "." symbols (e.g. 2.2.5, 10.2., etc).
			if (flag == true)
			{
				errors(ERRORS::INCORRECT_VALUE);
				return true;
			}

			// j gets the number of digits left, i.e. the power (e.g. in 10^2, j = 2).
			j = get_length(buffer) - (index + 1);

			// Go to the next digit.
			++index;

			// One "." detected. If there is another one, the value is invalid.
			flag = true;
		}
		// But if it is not a fraction, treat it like a normal number.
		coins = coins * 10 + (buffer[index] - '0');
	}

	coins /= power_10(j);

	return false;
}

bool get_info_transfer(const char* buffer, size_t& index, unsigned& sender, unsigned& receiver, double& coins)
{
	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	++index;

	if (!(is_digit(buffer[index])))
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	for (; is_digit(buffer[index]); ++index)
	{
		sender = sender * 10 + (buffer[index] - '0');
	}

	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	++index;

	if (!(is_digit(buffer[index])))
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	for (; is_digit(buffer[index]); ++index)
	{
		receiver = receiver * 10 + (buffer[index] - '0');
	}

	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	++index;

	if (!(is_digit(buffer[index])))
	{
		errors(ERRORS::SYNTAX_TRANSFER);
		return true;
	}

	coins_from_buffer(coins, buffer, index);

	return false;
}

bool get_info_wallet_info(const char* buffer, size_t& index, unsigned& id)
{
	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_ADD_WALLET);
		return true;
	}

	++index;

	if (!(is_digit(buffer[index])))
	{
		errors(ERRORS::SYNTAX_WALLET_INFO);
		return true;
	}

	for (; is_digit(buffer[index]); ++index)
	{
		id = id * 10 + (buffer[index] - '0');
	}

	return false;
}

bool get_info_order(const char* buffer, size_t& index, char* sub_buffer_2, char* sub_buffer_3, double& coins, unsigned& id)
{
	if (buffer[index] != ' ')
	{
		errors(ERRORS::SYNTAX_ORDER);
		return true;
	}

	++index;

	if (is_letter(buffer[index]))
	{
		for (size_t j = 0; buffer[index] != ' '; ++index, ++j)
		{
			sub_buffer_2[j] = buffer[index];
		}
	}
	else
	{
		errors(ERRORS::SYNTAX_ORDER);
		return true;
	}

	if (!are_equal(sub_buffer_2, "SELL") && !are_equal(sub_buffer_2, "BUY"))
	{
		errors(ERRORS::SYNTAX_ORDER);
		return true;
	}

	if (buffer[index] != ' ')
	{
		errors(ERRORS::INCORRECT_COMMAND);
		return true;
	}

	++index;

	if (is_digit(buffer[index]))
	{
		for (size_t k = 0; buffer[index] != ' '; ++index, ++k)
		{
			if (!buffer[index])
			{
				errors(ERRORS::SYNTAX_ORDER);
				return true;
			}

			sub_buffer_3[k] = buffer[index];
		}
	}
	else
	{
		errors(ERRORS::SYNTAX_ORDER);
		return true;
	}

	if (!buffer[index])
	{
		return true;
	}

	if (coins_from_buffer(coins, sub_buffer_3, 0) != 0)
	{
		return true;
	}

	++index;

	if (is_digit(buffer[index]))
	{
		for (; is_digit(buffer[index]); ++index)
		{
			id = id * 10 + (buffer[index] - '0');
		}
	}
	else
	{
		errors(ERRORS::INCORRECT_VALUE);
		return true;
	}

	return false;
}