/*
 * ImperialLength.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: dgv130030 and afb130030
 */

#include "ImperialLength.h"
#include <ostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Create an imperial length object using feet and inches
ImperialLength::ImperialLength(int feet, double inches)
{
	// store the length internally as (total) inches.
	totalInches = feet * 12.0 + inches;
}

ImperialLength::ImperialLength(double totalInches)
{
	// store the length internally as total inches.
	this->totalInches = totalInches;
}

ImperialLength::~ImperialLength()
{
	// nothing to do here
}

// convert to the number of feet
int ImperialLength::getFeet() const
{
	// get the total inches and divide by 12. Note that we don't want fractional feet
	return static_cast<int>(totalInches) / 12;
}

double ImperialLength::getInches() const
{
	// get the remaining inches. Calculate the number of remaining inches after removing all of the feet.
	// There may be a fractional inch since inches are store as a double value.
	return totalInches - (getFeet() * 12.0);
}

double ImperialLength::getTotalInches() const
{
	// just return the total inches
	return totalInches;
}

std::string ImperialLength::to_string(int precision) const
{
	// we use the output string stream to build the output for to_string.
	// Note that we set the precision for the output of the inches.
	// The format is xx'yy.yy" or yy.yy" if feet is 0.
	ostringstream outString;
	int feet = getFeet();

	if (feet != 0)
	{
		// output the feet
		outString << getFeet() << "'";
	}

	// output the inches
	outString << fixed << setprecision(precision) << getInches() << "\"";

	// return the string value of the ostringstream back to the caller
	return outString.str();
}
ImperialLength ImperialLength::operator+(const ImperialLength& right)
{
   // create temp object to not destroy data
   ImperialLength temp(1.0);
   temp = this->getTotalInches() + right.totalInches;
   return temp;
}

ImperialLength ImperialLength::operator-(const ImperialLength& right)
{
   // create temp object to not destroy data
   ImperialLength temp(1.0);
   temp = this->getTotalInches() - right.totalInches;
   return temp;
}

ImperialLength ImperialLength::operator-=(const ImperialLength& right)
{
   // set new value in object
   this->totalInches -= right.totalInches;
   return *this;
}

ImperialLength ImperialLength::operator+=(const ImperialLength& right)
{
   // set new value in object
   this->totalInches += right.totalInches;
   return *this;
}

ostream& operator<<(ostream& strm, const ImperialLength& right)
{
   // load info to ostream buffer and set precision
   strm << right.to_string(strm.precision());
   return strm;
}