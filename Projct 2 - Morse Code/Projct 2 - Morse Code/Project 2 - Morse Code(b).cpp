// Assignment 2 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// This program translates text input from user to Morse Code


#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// function prototypes
int buildTranslationArrays(char**, string**, ifstream&);
string userInput();
bool openfile(ifstream&);
void translate(string, char[], string[], int);


int main()
{
   char *englishLettersKey = nullptr;     // an array for storing the matching letters entered by the user
   string *MorseCodeKey = nullptr;        // an array for storing the morse code equivalents for englishLettersKey[]

   ifstream inputFile;
   while (!openfile(inputFile));           // if file is not opened successfully call the function again

   string englishSentence = userInput();  // call for user input of string

   int keysize = buildTranslationArrays(&englishLettersKey, &MorseCodeKey, inputFile);    // call function that builds englishLettersKey[] and MorseCodeKey[] and store to keysize
   translate(englishSentence, englishLettersKey, MorseCodeKey, keysize);                  // translate the user string

   cout << endl << endl;

   // delete dynamic memory and set pointers to nothing
   delete[] englishLettersKey;
   delete[] MorseCodeKey;
   MorseCodeKey = nullptr;
   englishLettersKey = nullptr;
   return 0;
}

// userInput() asks a user to enter a string but quits the program if the user enters "quit"
string userInput()
{
   string englishSentence;
   cout << "Please enter the sentence you wish to translate or type quit to exit the program: \n";
   getline(cin, englishSentence);
   if (englishSentence == "quit")
      exit(4);
   return englishSentence;
}

// openfile()
/*******************************************************************************************
* should be called from main in a loop. asks the user to enter the filename that is then   *
* opened. if the file fails to open main() calls the function again if called properly.    *
********************************************************************************************/
bool openfile(ifstream &inputFile)
{
   string filename;        // user-defined file

   cout << "Please enter the name of the mappings file or type quit to exit the program: ";
   getline(cin, filename);
   cout << endl;
   if (filename == "quit") // exit program if user enters "quit"
      exit(4);
   else
      inputFile.open(filename);

   if (!inputFile)         // if file does not open give an error message
   {
      cout << "The file \"" << filename << "\" could not be opened or does not exist.\n";
      return false;        // return to main with false indicating file was not opened successfully
   }
   return true;            // return to main with true indicating the file was opened successfully

}

// buildTranslationArrays()
/*******************************************************************************************
* takes two pointers and an ifstream file and reads into two seperate arrays. The first    *
* array contains the first char of each line in the file. the second array contains the    *
* rest of the line and stores as a string.                                                 *
********************************************************************************************/
int buildTranslationArrays(char **englishLetters, string **MorseCode, ifstream &translations)
{
   int translationsFileSize;
   translations >> translationsFileSize;                          // find size of file in first line
   *englishLetters = new char[translationsFileSize];              // allocate memory for array
   *MorseCode = new string[translationsFileSize];                 // allocate memory for array

   for (int count = 0; count < translationsFileSize; count++)
   {
      translations >> (*englishLetters)[count];                   // read char
      getline(translations, (*MorseCode)[count]);                 // read string
   }
   translations.close();   // close file

   return translationsFileSize;
}

// translate()
/*******************************************************************************************
* compares a character of a string to an array containing chars. if a space is detected,   *
* the function will skip that character and enter a space. if the values match, the        *
* the function prints the cooresponding array element in MorseCodeKey[] to the matching    *
* char. if nothing is matched, the program will print the unmatched character in quotes.   *
********************************************************************************************/
void translate(string userstring, char englishKey[], string MorseCodeKey[], int keysize)
{
   int length = userstring.length();

   cout << "\"" << userstring << "\"" << " translates to:\n";

   for (int currentChar = 0; currentChar < length; currentChar++)
   {
      for (int count = 0; count < keysize; count++)
      {
         if (userstring[currentChar] == ' ') // break if space is detected
            break;
         if (userstring[currentChar] == englishKey[count] || userstring[currentChar] == tolower(englishKey[count]))
         {
            cout << MorseCodeKey[count] << " ";
            break;   // match was found, break
         }
         else if (count == keysize - 1)   // no match found
            cout << "\"" << userstring[currentChar] << "\" ";
      }
   }
}