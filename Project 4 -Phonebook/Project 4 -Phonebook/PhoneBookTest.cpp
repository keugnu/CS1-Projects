#include "PhoneBook.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
   //  create phonebook and add entries
   PhoneBook purplePages;        // the phonebook
   purplePages.add("Jane Smith", "555-555-1212");
   purplePages.add("John Smith", "555-555-1122");
   purplePages.add("Ricky Gervais", "555-555-2211");
   purplePages.add("Ben Franklin", "555-555-1111");
   purplePages.add("Thomas Jefferson", "555-555-2222");
   purplePages.add("George Washington", "555-555-3333");
   purplePages.add("Alexander Hammilton", "555-555-3434");
   purplePages.add("Galileo Galilei", "555-555-4343");
   purplePages.add("Issac Newton", "555-555-3344");
   purplePages.add("Joseph Stalin", "555-555-4433");
   purplePages.add("Saddam Hussein", "555-555-5555");

   // give size and ask which entry to display
   cout << "The total number of entries is: " << purplePages.getSize() << endl << "Which entry to you want to retrieve? ";
   int call;
   PhoneEntry callEntry;      // a temp entry for storing calls
   cin >> call;
   callEntry = purplePages.PhoneEntryAt(call);
   cout << "The entry at position " << call << " is " << callEntry.getName() << "   " << callEntry.getNumber() << endl << endl;

   // show all entries
   for (int count = 0; count < purplePages.getSize(); count++)
   {
      callEntry = purplePages.PhoneEntryAt(count);
      cout << setw(20) << callEntry.getName() << "    " << setw(12) << callEntry.getNumber() << endl;
   }

   // remove an entry by name
   cout << "What name do you wish to remove from the phonebook? ";
   string name;
   cin.ignore(1000, '\n');
   getline(cin, name);
   purplePages.removeByName(name);
   cout << endl;

   // show all entries
   for (int index = 0; index < 10; index++)
   {
      callEntry = purplePages.PhoneEntryAt(index);
      cout << setw(20) << callEntry.getName() << "    " << setw(12) << callEntry.getNumber() << endl;
   }

   // remove an entry by number
   cout << endl << "What number do you wish to remove from the phonebook? ";
   string number;
   cin >> number;
   purplePages.removeByNumber(number);
   cout << endl;

   // show all entries
   for (int index = 0; index < 10; index++)
   {
      callEntry = purplePages.PhoneEntryAt(index);
      cout << setw(20) << callEntry.getName() << "    " << setw(12) << callEntry.getNumber() << endl;
   }

   cout << endl;
   return 0;
}