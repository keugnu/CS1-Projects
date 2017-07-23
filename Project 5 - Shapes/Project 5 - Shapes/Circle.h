// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Circle class definition

#ifndef CIRCLE_H
#define CIRCLE_H
#include "GeometricShape.h"

class Circle : public GeometricShape
{
private:
   double radius;
public:
   // constructors
   Circle(double newRadius)
   { radius = newRadius; }
   // accessors
   double Circle::getArea() const;
   double Circle::getPerimeter() const;
   std::string Circle::to_string() const
   { return "Circle radius (" + std::to_string(radius) + ")"; }
   // destructor
   ~Circle(){}
};


#endif