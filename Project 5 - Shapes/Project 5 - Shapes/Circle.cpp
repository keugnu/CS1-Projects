// Assignment 5 for CS 1337.006
// Programmer: Stephen-Michael Brooks
// Defining Circle class methods

#define _USE_MATH_DEFINES
#include "GeometricShape.h"
#include "Circle.h"
#include <math.h>

double Circle::getPerimeter() const
{
   // calculate circumference
   double circumference = 2 * M_PI * radius;
   return circumference;
}

double Circle::getArea() const
{
   // calculate area
   double area = M_PI * pow(radius, 2.0);
   return area;
}