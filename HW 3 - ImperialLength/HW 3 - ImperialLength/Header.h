/*
* ImperialLength.h
*
* This class implements imperial measurements (inches and feet).
*
* Currently the class allows you to create an imperial length object using
*  either feet and inches, or total inches.
*
*  You will be adding support for the operators +, =+, -, and =-
*
*  You will also be adding support for the << operator.
*
*  Created on: Apr 1, 2015
*      Author: dgv130030
*/

#ifndef IMPERIALLENGTH_H_
#define IMPERIALLENGTH_H_

#include <string>
#include <iostream>

using namespace std;

class ImperialLength
{
private:
   double totalInches;

public:
   ImperialLength(int feet, double inches);
   ImperialLength(double totalInches);
   ~ImperialLength();
   string to_string(int precision = 6) const;
   int getFeet() const;
   double getInches() const;
   double getTotalInches() const;
   ImperialLength operator+(const ImperialLength&);
   ImperialLength operator-(const ImperialLength&);
   ImperialLength operator-=(const ImperialLength&);
   ImperialLength operator+=(const ImperialLength&);
   friend ostream& operator<<(ostream&, const ImperialLength&);

};

#endif /* IMPERIALLENGTH_H_ */