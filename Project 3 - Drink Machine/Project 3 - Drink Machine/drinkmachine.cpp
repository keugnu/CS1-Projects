// Assignment 3 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Description: This program is a vending machine for cold drinks


// DrinkMachine implementation
// 
// This file implements the DrinkMachine. It will
// read in the file that contains the initial drink 
// information.
//
// It will also take care of the management of the drinks 
// being purchased by the customer. The functions will
// be called by the drinkMachineDrive.cpp code. 
#include "drinkmachine.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int INVALID_INDEX = -1;    // used for input errors and used to initialize certain variables to indicate if they are updated properly

// create()
/*********************************************************************************************
* This function initializes all values of the DrinkMachine structure and then it dynamically *
* allocates memory for an array of type DrinkItem and initializes each element of the        *
* DrinkItem structure. All data is read from a _binary_ file.                                *
**********************************************************************************************/
DrinkMachine* create()
{
   DrinkMachine *CheapDrinksCo = new DrinkMachine;       // allocate memory for DrinkMachine structure
   int numberOfOptions;
   CheapDrinksCo->version = 1;
   CheapDrinksCo->idNow = INVALID_INDEX;                 // initialed INVALID_INDEX for error detection

   ifstream inventoryInput;
   inventoryInput.open("drink_machine.txt");
   if (!inventoryInput.fail()) // if file is opened successfully
   {
      inventoryInput >> numberOfOptions;
      CheapDrinksCo->inventory = numberOfOptions;
      CheapDrinksCo->items = new DrinkItem[numberOfOptions];

      for (int count = 0; count < numberOfOptions; count++)
      {
         CheapDrinksCo->items[count].id = count + 1;
         inventoryInput >> CheapDrinksCo->items[count].name
            >> CheapDrinksCo->items[count].price
            >> CheapDrinksCo->items[count].inStock;
         CheapDrinksCo->items[count].sold = 0;
      }
      inventoryInput.close();
   }
   else // if file was not opened successfully
      cout << "Fatal error. drink_machine.txt could not be opened.";

	return CheapDrinksCo;
} // end create();

// firstDrink()
/********************************************************************************************
* This function checks to make cure that the create() function was successful and if so it  *
* sets an error condition returns a nullptr.                                                *
*********************************************************************************************/
DrinkItem* firstDrink(DrinkMachine *pDrink)
{
   
   if ((*pDrink).items != nullptr)  // create() was successful
   {
      (*pDrink).idNow = 0;
      return (*pDrink).items;
   }
   else  // create() was not successful
   {
      (*pDrink).idNow = INVALID_INDEX;
      return nullptr;
   }
} // end firstDrink();

// nextDrink()
/*********************************************************************************************
* This function checks to make sure that the firstDrink function was successful and if so it *
* increments idNow and returns the address of the next DrinkItem.                            *
**********************************************************************************************/
DrinkItem* nextDrink(DrinkMachine *pDrink)
{
   if (pDrink->idNow == INVALID_INDEX) // firstDrink() was unsuccessful
      return nullptr;
   else
      ++(pDrink->idNow);

   if (pDrink->idNow < pDrink->inventory)
      return &(pDrink->items[pDrink->idNow]);
   else // firstDrink() was successful
      return nullptr;
} // end nextDrink();

// dumpDrinkMachine()
/*********************************************************************************************
* This function prints the DrinkMachine with all DrinkItem elements to the console with all  *
* of the inventory information.                                                              *
**********************************************************************************************/
void dumpDrinkMachine(DrinkMachine* pDrink)
{
   cout << setw(2) << "ID" << setw(15) << "Name" << setw(6) << "Price" << setw(4) << "Qty" << setw(5) << "Sold" << endl;
   
   for (int count = 0; count < pDrink->inventory; count++)
   {
      cout << setw(2) << pDrink->items[count].id << setw(15) << pDrink->items[count].name << setw(6) << setprecision(2) << fixed << pDrink->items[count].price << setw(4) << pDrink->items[count].inStock << setw(5) << pDrink->items[count].sold << endl;
   }
} // end dumpDrinkMachine();

// items() returns the number of drink options
int items(DrinkMachine *pDrink)
{
   return pDrink->inventory;
} // end items();

// available() determines if the choice is in stock
bool available(DrinkMachine* pDrink, int itemID)
{
   bool isAvailable = true;

   if (itemID > pDrink->inventory)
      isAvailable = false;
   if (itemID < 1)
      isAvailable = false;
   if (pDrink->items[itemID - 1].inStock < 1)
      isAvailable = false;

   return isAvailable;
} // end available;

// cost() returns the cost of an item
double cost(DrinkMachine* pDrink, int itemID)
{
   if (itemID <= pDrink->inventory)
      return pDrink->items[itemID].price;
   else
      return -0.0001;
} // end cost();

// purchase()
/***********************************************************************************************
* This function checks to make sure that the user input a valid choice and then checks if      *
* the user input is in stock and then checks if the money put into the machine is sufficient   *
* to purchase the drink. If all is true, then the function purchases the drink by incrementing *
* the sold count and decrementing the inventory of that item then and also calculates change   *
************************************************************************************************/
Purchase purchase(DrinkMachine* pDrink, int itemID, double paid, double &change)
{
   bool isAvailable = true;
   isAvailable = available(pDrink, itemID);

   if (itemID < 0 && itemID > pDrink->inventory)                   // not a valid choice
      return Purchase::INVALID;

   else if (!isAvailable)                                          // not in stock
         return Purchase::NOT_AVAILABLE;

   else if (isAvailable && paid < pDrink->items[itemID - 1].price) // in stock but user did not pay enough
   {
      change = cost(pDrink, itemID);
      return Purchase::INSUFFICIENT_FUNDS;
   }
      

   else if (isAvailable && paid >= pDrink->items[itemID - 1].price) // in stock and user paid enough
   {
      change = paid - (pDrink->items[itemID - 1].price);
      --(pDrink->items[itemID - 1].inStock);
      ++(pDrink->items[itemID - 1].sold);
      return Purchase::PURCHASED;
   }

} // end purchase();

// destory() deletes all dynamically allocated memory used in the program.
void destroy(DrinkMachine *pDrinkMachine)
{
   delete [] pDrinkMachine->items;
   delete pDrinkMachine;
}

