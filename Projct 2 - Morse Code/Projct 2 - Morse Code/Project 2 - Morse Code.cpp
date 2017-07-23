// Assignment 2 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// This program translates text input from user to Morse Code

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// function prototypes
string userInput();          
void translate(char*, int);   
void display(string);

int main()
{
   string english = userInput();          // call function to ask user for english string to translate and store
   int size = english.length() + 1;       // to store size of user string

   char *cstr_english = new char[size];   // dynamically create array to store user string
   strcpy(cstr_english, english.c_str()); // convert string to cstring

   translate(cstr_english, size);         // call function to translate the english string
   return 0;
}

string userInput()
{
   string originalSentence;
   cout << "Please type a sentenece that you wish to translate or type quit to exit the program.... \n\n";
   getline(cin, originalSentence);
   if (originalSentence == "quit") // if user types quit, exit the program
      exit(4);

   return originalSentence;
}

void translate(char *english, int sizeOfenglish)
{
   ifstream inputFile;
   string filename,
          morseText;
   int sizeOfFile;

   // input validation loop for input file called by user
   for (bool opened = false; opened == false && filename != "quit";)
   {
      cout << "Please enter the mappings file for the translation or type quit to exit the program: ";
      cin >> filename;

      inputFile.open(filename);

      if (inputFile.fail())
         cout << "The file could not be opened.\n";
      else
         opened = true;
   }

   if (filename == "quit")    // if user entered quit, exit the program
      exit(4);

   inputFile >> sizeOfFile;   // store first line of input file to sizeOfFile, because it contains the number of lines in the file

   char *morseTranslations = new char[sizeOfFile * 2];    // dynamically create an array for the input file

   // building input file array
   for (int count = 0; count < sizeOfFile; count++)
      getline(inputFile, morseTranslations[count]);

   for (int currentChar = 0; currentChar < sizeOfenglish; currentChar++)
   {
      for (int count = 0; count < sizeOfFile; count++)
      {
         if (morseTranslations[count] == english[currentChar])
            morseText += morseTranslations[count];
      }
   }

   display(morseText);
}

void display(string morseText)
{
   cout << morseText << endl << endl;
}