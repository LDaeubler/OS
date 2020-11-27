
#define LOESUNG
#ifdef LOESUNG

#include <iostream>
using namespace std;

#include "math_lsg.hpp"
#include "datentypen_lsg.hpp"

int main()
{
	cout << "Uebung Nr. 2, Aufgabe 1" << endl;
	zahl a = 5;
	zahl b = 10;
	multiplikation(a, b);
	division(a, b);
	addition(a, b);
	subtraktion(a, b);
	system("pause");
	return 0;
}

#endif // LOESUNG

