#include "LongNumv2.h"

using namespace std;


int main()
{
	LongNumv2 a(123456, 78901651, true);
	LongNumv2 b(987654321);
	LongNumv2 c;

	c = a;
	a = a + b;
	cout << c << " + " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a = a - b;
	cout << c << " - " << b << " = " << a << endl;

	a = 12345678999;
	b = 987654321;
	c = a;
	a = a * b;
	cout << c << " * " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a = a / b;
	cout << c << " / " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a = a % b;
	cout << c << " % " << b << " = " << a << endl;

	system("pause");
	return 0;
}