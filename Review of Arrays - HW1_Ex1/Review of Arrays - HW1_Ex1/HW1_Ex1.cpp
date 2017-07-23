// Assignment 1 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Description: Creates and array of chars from an input file specified by the user then the
// array is printed in different orders making a picture.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int ROWS = 6,
          COLS = 6;

// function prototypes
void askforinput();
void createArray(ifstream &);
void drawArray(char[ROWS][COLS]);

int main()
{
   char quit = '\0';       // sentinel to detect the user wants to exit the program

   // loop to ask for user input
   while (quit != 'n')
   {
      askforinput();
      cout << endl;
      cout << "Are there any other files you wish to process? Enter any key to proceed or n for no: ";
      cin >> quit;
   }

   cout << endl << endl;
   return 0;
} // end function main()

//*************************************************************************//
// askforinput() is a function that asks the user fora  filename and when  //
// the user enters the filename it tried to open the file. if the file     //
// opens successfully , it begins processing by calling a new function. If //
// the file is not opened successfully, it gives and error message and     //
// returns to main();.                                                     //
//*************************************************************************//
void askforinput()
{
   ifstream inputFile;     // input file
   string filename;        // user-defined file
   
   cout << "Please enter the file you wish to process: ";
   cin >> filename;
   cout << endl << endl;

   inputFile.open(filename);

   if (!inputFile) // if file does not open give an error message and exit the function
      cout << "The file \"" << filename << "\" could not be opened.\n";
   else
   {
      createArray(inputFile);
      inputFile.close();
   }
} // end function askforinput()

//*************************************************************************//
// createArray() is a function that uses the input file that is passed     //
// into it as a parameter to create a 2D array of it's contents. The size  //
// is initialized globally. Once the array is complete, it calls a         //
// different function to print the array contents.                         //
//*************************************************************************//
void createArray(ifstream &inputFile)
{
   char array[ROWS][COLS];    // 2D array with size initialized globally

   for (int row = 0; row < ROWS; row++)
   {
      array[row][0] = inputFile.get();

      for (int col = 1; col < COLS; col++)
         array[row][col] = inputFile.get();

      inputFile.ignore(COLS + 1, '\n');   // skip new lines to prevent adding them to the array
   }

   drawArray(array);
} // end function createArray()


//*************************************************************************//
// drawArray() is a function that prints a 2D array in four different      //
// orders. First is left to right, top to bottom. Second is right to left, //
// top to bottom. Third is left to right, bottom to top. Fourth is right   //
// to left, bottom to top.                                                 //
//*************************************************************************//
void drawArray(char array[ROWS][COLS])
{
   // loops for top half of picture
   for (int rowTop = 0; rowTop < ROWS; rowTop++)
   {
      cout << array[rowTop][0];
      for (int colleft = 1; colleft < COLS; colleft++)
         cout << array[rowTop][colleft];

      for (int colright = COLS - 2; colright >= 0; colright--)
      {
         cout << array[rowTop][colright];
         if (colright == 0)
            cout << endl;
      }
   }

   // loops for bottom half of picture
   for (int rowBottom = ROWS - 1; rowBottom >= 0; rowBottom--)
   {
      cout << array[rowBottom][0];
      for (int colleft = 1; colleft < COLS; colleft++)
         cout << array[rowBottom][colleft];

      for (int colright = COLS - 2; colright >= 0; colright--)
      {
         cout << array[rowBottom][colright];
         if (colright == 0)
            cout << endl;
      }
   }
} // end function drawArray()