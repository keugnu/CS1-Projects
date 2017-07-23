#ifndef _DRINKMACHINE_H_
#define _DRINKMACHINE_H_
#include <string>
// All of your header file declarations for the DrinkMachine go here.
//
// The external structures and any functions that will be called by 
// the drinkMachineDrive will need to go here.
//
// Structure for a Drink Item
struct DrinkItem
{
   int id;
   std::string name;
   double price;
   int inStock;
   int sold;
};

// Structure for the Drink Machine
struct DrinkMachine
{
   int version = 1;
   int inventory;
   DrinkItem *items = nullptr;
   int idNow;
};

enum Purchase
{
   PURCHASED,
   INVALID,
   NOT_AVAILABLE,
   INSUFFICIENT_FUNDS
};


// Function prototypes
DrinkMachine* create();
void destroy(DrinkMachine *drinkMachine);
DrinkItem* firstDrink(DrinkMachine*);
DrinkItem* nextDrink(DrinkMachine*);
int items(DrinkMachine*);
bool available(DrinkMachine*, int);
double cost(DrinkMachine*, int);
Purchase purchase(DrinkMachine*, int, double, double&);
//void dumpDrinkMachine(DrinkMachine*);

#endif