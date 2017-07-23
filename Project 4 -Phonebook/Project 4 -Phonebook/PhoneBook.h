#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_
#include <string>

// phonebook classes
class PhoneEntry
{
private:
   std::string entryname;
   std::string entrynumber;
public:
   // constructors
   PhoneEntry()
   {}
   PhoneEntry(std::string setname, std::string setnumber)
   { entryname = setname; entrynumber = setnumber; }

   // mutators
   void setName(std::string setname);
   void setNumber(std::string setnumber);

   // accessors
   std::string getName() const;
   std::string getNumber() const;

   // destructor
   ~PhoneEntry()
   {}
};

class PhoneBook
{
private:
   static const int MAX_ENTRIES = 10;
   PhoneEntry entries[MAX_ENTRIES];
   int entryCount;
public:
   // constructors
   PhoneBook()
   { entryCount = 0; }

   // mutators
   void add(std::string, std::string);
   void removeByName(std::string);
   void removeByNumber(std::string);

   // accessors
   int getSize() const;
   const PhoneEntry &PhoneEntryAt(int) const;

   // destructor
   ~PhoneBook()
   {}
};

#endif
