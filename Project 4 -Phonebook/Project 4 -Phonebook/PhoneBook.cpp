// Project 4 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Description:
// This program creates a phonebook of 10 entries that the user can acceess and change.

#include "phonebook.h"
#include <iostream>
using namespace std;

// PhoneEntry methods
   // mutators
void PhoneEntry::setName(std::string setname)
{ entryname = setname; }
void PhoneEntry::setNumber(std::string setnumber)
{ entrynumber = setnumber; }

   // accessors
string PhoneEntry::getName() const
{ return entryname; }
string PhoneEntry::getNumber() const
{ return entrynumber; }


// PhoneBook methods
   // mutators
//**********************************************************************************
// Phonebook::add adds an entry to the phonebook.                                  *
//**********************************************************************************
void PhoneBook::add(string name, string number)
{
   if (entryCount == MAX_ENTRIES)
   {
      cout << "Entry limit reached. Please remove an entry before attempting to add another. " << endl;
      return;
   }
   PhoneEntry newEntry(name, number);
   entries[entryCount] = newEntry;
   entryCount++;
}

//**********************************************************************************
// PhoneBook::removeByName removes an entry from the phonebook by copying the      *
// last entry into the array index of the name that is to be removed, then the     *
// counter for the size of the phonebook is decremented by one so that the next    *
// addition to the phonebook will overwrite the last entry.                        *
//**********************************************************************************
void PhoneBook::removeByName(string name)
{
   string entryName;
   for (int count = 0; count < MAX_ENTRIES; count++)
   {
      entryName = entries[count].getName();
      if (name == entryName)
      {
         PhoneEntry copy(entries[entryCount - 1].getName(), entries[entryCount - 1].getNumber());
         entries[count] = copy;
         entryCount--;
      }
   }
   
}

//**********************************************************************************
// PhoneBook::removeByNumber removes an entry from the phonebookby copying the     *
// last entry into the array index of the number that is to be removed, then the   *
// counter for the size of the phonebook is decremented by one so that the next    *
// addition to the phonebook will overwrite the last entry.                        *
//**********************************************************************************
void PhoneBook::removeByNumber(string number)
{
   string entryNumber;
   for (int count = 0; count < MAX_ENTRIES; count++)
   {
      entryNumber = entries[count].getNumber();
      if (number == entryNumber)
      {
         PhoneEntry copy(entries[entryCount - 1].getName(), entries[entryCount - 1].getNumber());
         entries[count] = copy;
         entryCount--;
      }
   }
}
   // accessors
int PhoneBook::getSize() const
{ return entryCount; }

//**********************************************************************************
// PhoneEntry::PhoneEntryAt finds the entry of the phonebook specific by the user  *
// by index. If the user entrers a number less than 0, it returns the 0th entry.   *
// If the user enters a number greater than 9, it returns the 10th entry.          *
//**********************************************************************************
const PhoneEntry &PhoneBook::PhoneEntryAt(int position) const
{
   int returnEntry;

   if (position < 0)
      returnEntry = 0;
   else if (position > MAX_ENTRIES-1)
      returnEntry = entryCount - 1;
   else
      returnEntry = position;
   
   return entries[returnEntry];
}