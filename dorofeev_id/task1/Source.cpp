#include "LongNum.h"

using namespace std;


int main()
{
	LongNum a(123456);
	LongNum b(987654);
	LongNum c;

	c = a;
	a += b;
	cout << c << " + " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a -= b;
	cout << c << " - " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a *= b;
	cout << c << " * " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a /= b;
	cout << c << " / " << b << " = " << a << endl;

	a = 123456;
	b = 987654;
	c = a;
	a %= b;
	cout << c << " % " << b << " = " << a << endl;

	system("pause");
	return 0;
}