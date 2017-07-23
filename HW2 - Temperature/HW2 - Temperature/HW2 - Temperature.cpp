// Homework #2 for CS 1337.006
// Programmer: Stephen-Michael Brooks

#include <iostream>
using namespace std;

class Temperature
{
private:
	double temperature;

public:
	// constructors
	Temperature()
	{ temperature = 0; }

	// mutators
	void setCelsius(double temp)
	{ temperature = temp; }
	void setFahrenheit(double);

	// accessors
	double getCelsius() const
	{ return temperature; }
	double getFahrenheit() const;
};

int main()
{
	Temperature temp;

	double fahrenheit, 
		    celsius;

	cout << "Enter a temperature in Celsius: ";
	cin >> celsius;
	temp.setCelsius(celsius);
	cout << temp.getCelsius() << " C is " << temp.getFahrenheit() << " F\n";
	cout << "Enter a temperature in Fahrenheit: ";
	cin >> fahrenheit;
	temp.setFahrenheit(fahrenheit);
	cout << temp.getFahrenheit() << " F is " << temp.getCelsius() << " C\n";
	return 0;
}

double Temperature::getFahrenheit() const
{
   // convert
	double temp = ((temperature * 9 / 5) + 32);
	return temp;
}

void Temperature::setFahrenheit(double temp)
{
   // convert
	temperature = ((temp - 32)* 5 / 9);
}