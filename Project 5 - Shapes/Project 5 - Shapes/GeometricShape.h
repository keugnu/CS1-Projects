// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// GeometricShape class definition

#ifndef GEOMETRIC_SHAPE_H
#define GEOMETRIC_SHAPE_H

#include <string>
#include <sstream>

class GeometricShape
{
public:
   // accessors
   virtual double getArea() const = 0;
   virtual double getPerimeter() const = 0;
   // overloaded operators
   virtual std::string to_string() const = 0;
   // destructor
   virtual ~GeometricShape(){}
};

// global function prototypes
std::ostream& operator<<(std::ostream&, const GeometricShape&);

#endif