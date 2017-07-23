// Assignment 6 for CS 1337.006
// Programmer: Stphen-Michael Brooks
// Description:
// This program determines if the user input is a palindrome.

#include <iostream>
#include <string>
#include <locale>

using namespace std;


// function prototypes
string stripString(const string &inputString);
bool is_palindrome(const string &testString);

int main()
{
   string inputLine, testString;
   // read in strings of text and check to see if they are palindromes
   do
   {
      cout << "Enter text. Just hit enter to stop processing\n";
      getline(cin, inputLine);
      testString = stripString(inputLine);
      if (testString != "")
      {
         cout << "New string is \"" << testString << "\"\n";
         cout << "The string is " 
              << (is_palindrome(testString) ? "" : "not ")
              << "a palindrome\n";
      }
   } while (testString != "");
   
   cout << "\nThe program has ended.\n";
      return 0;
}

// Take a string and remove any characters that are
// not alphabetic or numeric. Covert any upper case
// letters to lower case.
string stripString(const string &inputString)
{
   // string to be returned
   string newString;
   // keep alpha-numeric characters only and
   // convert them to lower case.
   for (auto currentCharacter : inputString)
   {
      // if the character is alphabetic or numeric we want to keep it
      if (isalnum(currentCharacter))
      {
         // make sure it is lower case and add it to the new string
         newString += tolower(currentCharacter);
      }
   }
   // return back the new string that has only alpha-numeric
   return newString;
}

bool is_palindrome(const string &testString)
{
   // your code goes here.You may need other functions to
   // make the recursion work. You need to return true if it
   // is a palindrome and false if not

   // make sure string is not empty and if so, return true
   if (testString == "")
      return true;

   // assign first and last letter of parameter string to chars
   char firstletter = testString.at(0);
   char lastletter = testString.at(testString.length() - 1);
   
   // if parameter has 2 or more characters, compare them. If not, return true
   if (testString.length() >= 2)
   {
      // compare first and last letters
      if (firstletter != lastletter)
         return false;
      else
         // recursive funtion call - eliminate first and last letters from parameter
         return is_palindrome(testString.substr(1, testString.length() - 2));
   }
   else true;
}