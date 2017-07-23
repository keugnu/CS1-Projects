// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Defining Rectangle class methods

#include "GeometricShape.h"
#include "Rectangle.h"

double Rectangle::getPerimeter() const
{
   // calculate perimeter
   double perimeter = (length + width) * 2.0;
   return perimeter;
}

double Rectangle::getArea() const
{
   // calculate area
   double area = length * width;
   return area;
}