#define LOESUNG
#ifdef LOESUNG

#include <iostream>
using namespace std;
#include "math_lsg.hpp"

zahl multiplikation(zahl a, zahl b)
{
	cout << a << "*" << b << "=" << (a*b) << endl;
	return a*b;
}

double division(zahl a, zahl b)
{
	cout << a << "/" << b << "=" << (static_cast<double>(a) / b) << endl;
	return static_cast<double>(a) / b;
}

zahl addition(zahl a, zahl b)
{
	cout << a << "+" << b << "=" << (a+b) << endl;
	return a + b;
}

zahl subtraktion(zahl a, zahl b)
{
	cout << a << "-" << b << "=" << (a - b) << endl;
	return a - b;
}

#endif // LOESUNG