// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Defining Triangle class methods

#include "GeometricShape.h"
#include "Triangle.h"

double Triangle::getPerimeter() const
{
   // calculate perimeter
   double perimeter = a + b + c;
   return perimeter;
}

double Triangle::getArea() const
{
   // calculate area using Heron's formula
   double halfperimeter = (a + b + c) * 0.5;
   double area, inner;
   inner = halfperimeter * (halfperimeter - a) * (halfperimeter - b) * (halfperimeter - c);
   area = pow(inner, 0.5);
   return area;
}