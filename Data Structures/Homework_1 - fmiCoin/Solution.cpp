#include <iostream>
#include <fstream>
#include "helper_functions.h"
#include "Wallet_Array.h"
#include "Transaction_Array.h"
#include "Order_Array.h"

// Using a buffer get and process the input. If it is a command then call the appropriate function. If not, give an error.
int main()
{
	// Open the files with an ofstream object in order to make sure they exist.
	validate_files();

	// Declare the arrays.
	Wallet_Array warr;
	Transaction_Array tarr;
	Order_Array oarr;

	// Indicates whether user wants to stop the program.
	bool is_not_quit = true;

	// Accept input as long as it is not "quit".
	do
	{
		// Stores the line which the user entered. Declared and defined in the do-while loop so as not to store the previous command.
		char buffer[1024] = { '\0' };

		std::cin.getline(buffer, 1024);

		// Stores the name of the command.
		char sub_buffer_1[20] = { '\0' };

		for (size_t i = 0; buffer[i] != '\0'; i++)
		{	
			// Copy the name of the command.
			for (; buffer[i] != ' ' && buffer[i] != '\0'; ++i)
			{
				sub_buffer_1[i] = buffer[i];
			}

			//-------------------------------------------------------------------------------------------------------------- ADD-WALLET
			if (are_equal(sub_buffer_1, "add-wallet"))
			{
				// Initialize a variables to hold the size of the information. Add one to the ID otherwise the first wallet will id = 0.
				double fiat = 0;
				char name[SIZE_NAME] = { '\0' };

				// Checks for validity and evaluates the variabels. Converts to bool like rename().
				if (get_info_add_wallet(buffer, i, fiat, name) != 0)
				{
					break;
				}

				// Add a wallet and a transaction to the appropriate arrays.
				warr.add(name, fiat, tarr);
			}
			//-------------------------------------------------------------------------------------------------------------- TRANSFER
			else if (are_equal(sub_buffer_1, "transfer"))
			{
				unsigned sender = 0, receiver = 0;
				double coins = 0;

				if (get_info_transfer(buffer, i, sender, receiver, coins) != 0)
				{
					break;
				}

				// Validate that the sender has enough coins.
				double current_coins = tarr.get_coins(sender);

				if (current_coins < 0)
				{
					break;
				}

				if (current_coins < coins)
				{
					errors(ERRORS::NO_COINS);
					break;
				}

				// What will happen if we have an id that has an unapproved SELL order and then transfers more coins than currently selling?
				// Check the offers to prevent that.
				if (current_coins - oarr.coins_for_sell(sender) < coins)
				{
					errors(ERRORS::SELLING_MORE);
					break;
				}

				tarr.add(sender, receiver, coins);

				// Because the buffer's index is still not at the end (coins_from_buffer() in get_info_transfer() takes it as a copy), break.
				break;
			}
			//-------------------------------------------------------------------------------------------------------------- MAKE-ORDER
			else if (are_equal(sub_buffer_1, "make-order"))
			{
				// Store the type here.
				char sub_buffer_2[5] = { '\0' };

				double coins = 0;

				// Store the number here. Used because there are more digits after the number and j will not evaluate correctly (e.g. in "make-order SELL 0.5 1", j = 3 and should be 1).
				char sub_buffer_3[10] = { '\0' };

				// Get the id from the characters.
				unsigned id = 0;

				if (get_info_order(buffer, i, sub_buffer_2, sub_buffer_3, coins, id) != 0)
				{
					break;
				}

				// Initialize a variable to store the number of transfers that occur from the order.
				size_t number_transfers = 0;

				// Initialize a variabe to store the total amount of coins exchanged. Later multiply it by EXCHANGE RATE and get the total value in fiatMoney.
				double total_coins = 0;

				// If the type is SELL.
				if (are_equal(sub_buffer_2, "SELL"))
				{
					// Validate the coins and the ID.
					if (tarr.get_coins(id) - oarr.coins_for_sell(id) < coins)
					{
						errors(ERRORS::NO_COINS);
						break;
					}

					oarr.sell(id, coins, total_coins, number_transfers, warr, tarr);
				}
				else // It is a BUY.
				{
					// Check whether buyer has enough fiatMoney to buy the wanted amount of fmiCoins.
					if (warr.check_fiat(id, coins) != 0)
					{
						break;
					}

					oarr.buy(id, coins, total_coins, number_transfers, warr, tarr);
				}
			}
			//-------------------------------------------------------------------------------------------------------------- WALLET-INFO
			else if (are_equal(sub_buffer_1, "wallet-info"))
			{
				// Get the ID from the characters.
				unsigned id = 0;

				if (get_info_wallet_info(buffer, i, id) != 0)
				{
					break;
				}

				warr.wallet_info(id, tarr);
			}
			//-------------------------------------------------------------------------------------------------------------- ATTRACT-INVESTORS
			else if (are_equal(sub_buffer_1, "attract-investors"))
			{
				Wallet_Array warr2 = warr;

				if (warr2.attract_investors(tarr) != 0)
				{
					break;
				}
			}
			//-------------------------------------------------------------------------------------------------------------- QUIT
			else if (are_equal(sub_buffer_1, "quit"))
			{
				// Write the the arrays to the appropriate files.
				warr.write();
				tarr.write();
				oarr.write();

				// Set the flag to false.
				is_not_quit = false;

			// USED FOR DEBUGGING -------------------------------------------------------------------------------------------------------------- OPTIONAL
				Wallet_Array warr2;
				Transaction_Array tarr2;
				Order_Array oarr2;
				
				std::cout << "\n\n\nContent of wallets.dat:\n\n";
				warr2.print();

				std::cout << "\n\n\nContent of transactions.dat:\n\n";
				tarr2.print();

				std::cout << "\n\n\nContent of orders.dat:\n\n";
				oarr2.print();
			// USED FOR DEBUGGING -------------------------------------------------------------------------------------------------------------- OPTIONAL			
			}
			else
			{
				errors(ERRORS::INCORRECT_COMMAND);
				break;
			}

		}

	} while (is_not_quit);

	return 0;
}