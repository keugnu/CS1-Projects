// Programmer:    Stephen-Michael Brooks
// Assignment:    Homework 1 - Sorting
// Class:         CS 1337.006
// Desription:    This program fills an array of a size dictated by the user and fills with random numbers. It then sorts the array
//                and displays the first and last element of the array.

#include <iostream>
#include <ctime>
#include <utility>
using namespace std;

// Function prototypes
void userInput(int&);
void fillArrayRandom(int[], int);
void sort(int[], int);


int main()
{
   int size;                  // To declare array size
   int *array = nullptr;      // Set pointer to nothing to prevent corruption
   
   userInput(size);                 // Ask user to declare size of array
   array = new int[size];           // Create memory for new array
   fillArrayRandom(array, size);    // Initialize all array elements with random number
   sort(array, size);               // Bubble sort
   cout << endl << endl; 

   // Printing information about array
   cout << "The size of the array is " << size << " elements.\n"
        << "\nThe first element is " << array[0] << ".\n" 
        << "The last element is " << array[size - 1] << ".\n\n";

   delete[] array;   // Deleting array
   array = nullptr;  // Set pointer to nothing to prevent corruption

   return 0;
} // end function main()

// userInput()
/*******************************************************************
* Asks user to enter an integer greater than zero. The variable is *
* passed by reference.                                             *
********************************************************************/
void userInput(int &size)
{
   cout << "Please enter an integer greater than zero: ";
   cin >> size;

   while (size < 1)  // Input validation loop
   {
      cout << "That is not a valid entry. Number must be a positive integer.\nPlease enter an integer greater than zero: ";
      cin >> size;
   }
} // end function userInput()

// fillArrayRandom()
/*******************************************************************
* Traverse an array and initializes each element with a random     *
* integer between 1 and 1000.                                      *
********************************************************************/
void fillArrayRandom(int array[], int size)
{
   srand(time(0));   // set time for rand()
   for (int count = 0; count < size; count++)
      array[count] = (rand() % 1000 + 1);
} // end function fillArrayRandom()

// sort()
/*******************************************************************
* Compares each element of an array to the next and tests if       *
* its value is larger. If it is, the two elements switch position  *
* in the array. The loop will run until no swaps are performed.    *
********************************************************************/
void sort(int array[], int size)
{
   bool ifswapped;

   if (array == nullptr)
      cout << "Cannot perform the sort. Array is not allocated.\n";

   do
   {
      ifswapped = false;   // Assume no swaps have happened

      for (int count = 0; count < (size - 1); count++)
      {
         if (array[count] > array[count + 1])
         {
            swap(array[count], array[count + 1]);
            ifswapped = true;    // Set true because a swap was performed
         }
      }

   } while (ifswapped);
} // end function sort()