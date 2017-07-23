// Assignment 3 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Description: This program is a vending machine for cold drinks. The machine is maintained with a binary file.


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
#include <istream>

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

   ifstream inventoryInput ("drink_machine.bin", ios::binary);
   if (!inventoryInput.fail()) // if file is opened successfully
   {
/*                                   BINARY FILE OFFSET KEY

     Offset   Type             Size    Description
         0    int                4     Number of drinks that follow

first    4    char array[16]     16    Null terminated name of the first drink
         20   double             8     Price of the first drink
         28   int                4     Quantity.The number of drinks of this kind in the machine
         32   int                4     Purchased: The number of drinks if this kind that have been purchased

second   36   char array[16]     16    Null terminated name of the second drink
         52   double             8     Price of the second drink
         60   int                4     Quantity.The number of drinks of this kind in the machine
         64   int                4     Purchased: The number of drinks if this kind that have been purchased
                                                                                                         
         ----------------------repeat for number of drinks 32 bytes each----------------------
*/
      inventoryInput.read(reinterpret_cast<char*>(&numberOfOptions), sizeof(numberOfOptions));
      CheapDrinksCo->inventory = numberOfOptions;
      CheapDrinksCo->items = new DrinkItem[numberOfOptions];

      for (int count = 0; count < numberOfOptions; count++)
      {
         CheapDrinksCo->items[count].id = count + 1;

         char *nameOfDrink = new char[16];
         inventoryInput.read(nameOfDrink, 16);
         string name(nameOfDrink);
         CheapDrinksCo->items[count].name = name;

         inventoryInput.read(reinterpret_cast<char*>(&(CheapDrinksCo->items[count].price)), sizeof(CheapDrinksCo->items[0].price));
         inventoryInput.read(reinterpret_cast<char*>(&(CheapDrinksCo->items[count].inStock)), sizeof(CheapDrinksCo->items[0].inStock));
         inventoryInput.read(reinterpret_cast<char*>(&(CheapDrinksCo->items[count].sold)), sizeof(CheapDrinksCo->items[0].sold));

         delete[]nameOfDrink;    // delete for reuse
      }
      inventoryInput.close();
   }
   else // if file is not opened successfully
      cout << "Fatal error. drink_machine.bin could not be opened.";

	return CheapDrinksCo;
} // end create();

// firstDrink()
/********************************************************************************************
* This function checks to make cure that the create() function was successful and if so it  *
* sets an error condition returns a nullptr.                                                *
*********************************************************************************************/
DrinkItem* firstDrink(DrinkMachine *pDrink)
{
   
   if (pDrink->items != nullptr) // create() was successful
   {
      pDrink->idNow = 0;
      return pDrink->items;
   }
   else // create() was unsuccessful
   {
      pDrink->idNow = INVALID_INDEX;
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
   else // firstDrink() was successful
      ++(pDrink->idNow);

   if (pDrink->idNow < pDrink->inventory) // do not go over bounds of array
      return &(pDrink->items[pDrink->idNow]);
   else
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
      return pDrink->items[itemID - 1].price;
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
   isAvailable = available(pDrink, itemID); // check if item is in stock

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
      change = (paid - pDrink->items[itemID - 1].price);
      --(pDrink->items[itemID - 1].inStock);
      ++(pDrink->items[itemID - 1].sold);
      return Purchase::PURCHASED;
   }
} // end purchase();

// destory()
/*********************************************************************************************
* This function first updates the quantities of instock and sold values in the binary file   *
* then deletes all dynamically allocated memory used in the program.                         *
**********************************************************************************************/
void destroy(DrinkMachine *pDrinkMachine)
{
   fstream updateMachine ("drink_machine.bin", ios::out | ios::in | ios::binary);

   if (updateMachine.is_open()) // if file opened successfully
   {
      updateMachine.clear();
      updateMachine.seekp(4L, ios::beg); // skip first 4 bytes
      for (int count = 0; count < pDrinkMachine->inventory; count++)
      {
         updateMachine.seekp(24L, ios::cur);
         updateMachine.write(reinterpret_cast<char*>(&(pDrinkMachine->items[count].inStock)), sizeof(pDrinkMachine->items[count].inStock));
         updateMachine.write(reinterpret_cast<char*>(&(pDrinkMachine->items[count].sold)), sizeof(pDrinkMachine->items[count].sold));
      }
      updateMachine.close();
   }
   else // if file could not be opened
      cout << "Fatal error. drink_machine.bin could not be updated.";

   delete [] pDrinkMachine->items;  // delete dynamic memory
   delete pDrinkMachine;            // delete dynamic memory
} // end destroy();

