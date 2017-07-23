#ifndef _DRINKMACHINE_H_
#define _DRINKMACHINE_H_
#include <string>

// Structure for a Drink Item
struct DrinkItem
{
   int id;                       // ID of an item for the user
   std::string name;             // name of an item
   double price;                 // price of an item
   int inStock;                  // store the quantity of an item in the machine
   int sold;                     // stores how many of an item has been purchased
};

// Structure for the Drink Machine
struct DrinkMachine
{
   int version;                  // version of this program
   int inventory;                // stores the number of options (number of DrinkItem elements)
   DrinkItem *items = nullptr;   // to be an array - initialized to nullptr to prevent corruption of unrelated data
   int idNow;                    // used for selection of a DrinkItem element
};

enum Purchase
{
   PURCHASED,           // 0
   INVALID,             // 1
   NOT_AVAILABLE,       // 2
   INSUFFICIENT_FUNDS   // 3
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

#endif