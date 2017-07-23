// drinkMachineDriver.cpp
// 
// This code makes use of the drinkmachine.h support
//
// This code provides the external user interface for the 
// drink machine. 
//
#include "drinkmachine.h"
#include <iostream>
#include <iomanip>

using namespace std;

int getDrinkId(DrinkMachine *pDrinkMachine);
void displayMenu(DrinkMachine *pDrinkMachine);
double getCustomerAmount();
void dumpDrinkMachine(DrinkMachine *pDrinkMachine);

int main()
{
	const int QUIT = 0;

	// pointer to the drink machine
	DrinkMachine *pDrinkMachine = nullptr;
	// used to control the main processing loop
	bool finished = false;
	// drink id from the customer or QUIT if exiting
	int drinkId;

	// Create the drink machine
	// cout << "Create the drink machine\n";
	pDrinkMachine = create();

	if (pDrinkMachine == nullptr)
	{
		cout << "The drink machine could not be created\n";
		exit(4);
	}

	// display the contents of the drink machine
	dumpDrinkMachine(pDrinkMachine);

	do
	{
		// Get the drink id of the next drink to be purchased
		drinkId = getDrinkId(pDrinkMachine);

		if (drinkId != QUIT)
		{
			// process the purchase of a drink
			double amount;
			double change;
			Purchase result;

			// get the amount from the customer
			amount = getCustomerAmount();

			// purchase the drink 
			result = purchase(pDrinkMachine, drinkId, amount, change);
				
			switch (result)
			{
				// The drink has been purchased
				case Purchase::PURCHASED:
					cout << "Your drink has been purchased.";

					if (change > 0.0)
					{
						cout << setprecision(2) << fixed;
						cout << " Your change is $ " << change;
					}
					cout << endl;
					break;

				// The drink is not available (out of supply)
				case Purchase::NOT_AVAILABLE:
					cout << "Sorry, we are out of your drink. Please select another drink\n";
					break;

				// The user did not provide enough money to purchase the drink
				case Purchase::INSUFFICIENT_FUNDS:
					cout << "The amount you entered is insufficient to purchase the drink. ";
					cout << "The price is " << change << endl;
					break;

				// The call was invvalid or some other programming error
				case Purchase::INVALID:
					cout << "Unexpected result - internal error INVALID" << endl;
					break;

				// Unexpected error back from purchase. Programming error.
				default:
					cout << "Unexpected result - internal error " << static_cast<int>(result) << endl;
					break;
			}
		}
		else
		{
			// we are quitting
			finished = true;
		}
	} while (!finished);

	// display the contents of the drink machine again. 
	dumpDrinkMachine(pDrinkMachine);

	cout << endl << "Thank you for using the drink machine." << endl;
	
	// clean up the drink machine
	destroy(pDrinkMachine);

	// return to the operating system. 
	return 0;
}

// get the drink id from the user
int getDrinkId(DrinkMachine *pDrinkMachine)
{
	int drinkId;
	bool valid;

	do
	{
		// display the drink menu
		displayMenu(pDrinkMachine);
		// get the drink id
		cin >> drinkId;

		if (drinkId < 0 || drinkId > items(pDrinkMachine))
		{
			// invalid drink id
			cout << "The drink id is not valid.\n";
			valid = false;
		}
		else
		{
			// it is valid
			valid = true;
		}
	} while (!valid);

	return drinkId;
}

// display the menu for the drink machine
void displayMenu(DrinkMachine *pDrinkMachine)
{
	// widths used to display the menu
	const int ID_WIDTH = 10;
	const int NAME_WIDTH = 15;
	const int PRICE_WIDTH = 9;

	// display the directions for the menu
	cout << "Enter a drink id for the drink you want to purchase or 0 to quit.\n";
	cout << setw(ID_WIDTH) << "Drink id";
	cout << setw(NAME_WIDTH) << "Drink";
	cout << setw(PRICE_WIDTH) << "Price" << endl;

	cout << setprecision(2) << fixed;

	// display the drinks items
	DrinkItem *pDrink = nullptr;
	for (pDrink = firstDrink(pDrinkMachine); pDrink != nullptr; pDrink = nextDrink(pDrinkMachine))
	{
		cout << setw(ID_WIDTH) << pDrink->id;
		cout << setw(NAME_WIDTH) << pDrink->name;
		cout << "  $ " << setw(PRICE_WIDTH-4) << pDrink->price << endl;
	}
}

double getCustomerAmount()
{
	double amount;
	bool valid;

	do
	{
		cout << "Enter the amount for the purchase (up to $2.00): ";
		cin >> amount;

		if (amount >= 0.0 && amount <= 2.00)
		{
			// valid amount
			valid = true;
		}
		else
		{
			// invalid amount
			cout << "The amount entered is not valid.\n";
			valid = false;
		}

	} while (!valid);

	return amount;
}