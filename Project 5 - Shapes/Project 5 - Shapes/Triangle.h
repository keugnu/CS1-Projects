// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Triangle class definition

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeometricShape.h"

class Triangle : public GeometricShape
{
private:
   double a, b, c;
public:
   // constructors
   Triangle(double sideA, double sideB, double sideC)
   { a = sideA; b = sideB; c = sideC; }
   // accessors
   double Triangle::getArea() const;
   double Triangle::getPerimeter() const;
   std::string Triangle::to_string() const
   { return "Triangle side A (" + std::to_string(a) + ")" + " side B (" + std::to_string(b) + ")" + " side C (" + std::to_string(c) + ")"; }
   // destructor
   ~Triangle(){}
};


#endif