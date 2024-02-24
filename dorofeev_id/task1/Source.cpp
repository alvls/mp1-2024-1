#include "LongNumv2.h"

using namespace std;


int main()
{
	LongNumv2 a(123456);
	LongNumv2 b(987654);
	LongNumv2 c;

	c = a;
	a = a + b;
	cout << c << " + " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a = a - b;
	cout << c << " - " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
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