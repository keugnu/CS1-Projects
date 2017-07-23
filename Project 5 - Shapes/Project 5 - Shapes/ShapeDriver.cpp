// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Descrition:
// This program creates geometric shapes and displays their type, area, perimeter, and attributes to the console.

#include "GeometricShape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <iostream>
#include <iomanip>

using namespace std;

// GLOBAL CONSTANTS
const int NUMBER_OF_SHAPES = 7;

int main()
{
   // create all shapes in array
   GeometricShape *shapes[NUMBER_OF_SHAPES] =
   {
      new Circle(7.0),
      new Circle(3.4),
      new Rectangle(2.2, 5.5),
      new Rectangle(9.0, 4.0),
      new Triangle(2.0, 3.0, 4.0),
      new Triangle(5.2, 1.5, 3.8),
      new Triangle(8.1, 8.0, 8.9)
   };

   // display area and perimeter of each shape
   for (int count = 0; count < NUMBER_OF_SHAPES; count++)
   {
      cout << fixed << setprecision(2);
      cout << "Shape " << count + 1 << endl;
      cout << "Area is " << shapes[count]->getArea() << endl;
      cout << "Perimeter is " << shapes[count]->getPerimeter() << endl << endl;
   }

   cout << endl;

   // display attributes of each shape
   for (int count = 0; count < NUMBER_OF_SHAPES; count++)
      cout << "Shape " << count + 1 << " " << shapes[count]->to_string() << endl << endl;
}

// overloading stream insertion operator for GeometricShape objects
ostream& operator<<(ostream &outputStream, const GeometricShape &right)
{
   outputStream << right.to_string();
   return outputStream;
}