// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Rectangle class definition

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "GeometricShape.h"

class Rectangle : public GeometricShape
{
private:
   double length, width;
public:
   // constructors
   Rectangle(double newWidth, double newLength)
   { width = newWidth; length = newLength; }
   // accessors
   double Rectangle::getArea() const;
   double Rectangle::getPerimeter() const;
   std::string Rectangle::to_string() const
   { return "Rectangle width (" + std::to_string(width) + ")" + " length (" + std::to_string(length) + ")"; }
   // destructor
   ~Rectangle(){}
};


#endif