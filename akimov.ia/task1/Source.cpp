#include <iostream>
#include <clocale>

using namespace std;

class RationalFraction
{
private:
	int numerator, denominator;
	int GreatestCommonDivisor(int a, int b)
	{
		if (a == 0)
			return 1;
		while (b != 0)
		{
			int temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}
public:
	RationalFraction()
	{
		numerator = 0;
		denominator = 1;
	}

	RationalFraction(int num, int denom)
	{
		int gcd = GreatestCommonDivisor(num, denom);
		numerator = num / gcd;
		denominator = denom / gcd;
	}

	RationalFraction operator+(const RationalFraction& other)
	{
		if (numerator == 0 && other.numerator == 0)
			return RationalFraction();
		int num = numerator * other.denominator + other.numerator * denominator;
		int denom = denominator * other.denominator;
		return RationalFraction(num, denom);
	}

	RationalFraction operator-(const RationalFraction& other)
	{
		if (numerator == 0 && other.numerator == 0)
			return RationalFraction();
		int num = numerator * other.denominator - other.numerator * denominator;
		int denom = denominator * other.denominator;
		return RationalFraction(num, denom);
	}

	RationalFraction operator*(const RationalFraction& other)
	{
		if (numerator == 0 || other.numerator == 0)
			return RationalFraction();
		int num = numerator * other.numerator;
		int denom = denominator * other.denominator;
		return RationalFraction(num, denom);
	}

	RationalFraction operator/(const RationalFraction& other)
	{
		if (numerator == 0)
			return RationalFraction();
		int num = numerator * other.denominator;
		int denom = denominator * other.numerator;
		return RationalFraction(num, denom);
	}

	void print()
	{
		cout << numerator << "/" << denominator << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	int r;
	do {
		system("cls");
		int num1, denom1, num2, denom2, flag;
		do
		{
			flag = 0;
			cout << "Введите числитель и знаменатель первой дроби: ";
			cin >> num1 >> denom1;
			if (denom1 == 0)
			{
				system("cls");
				cout << "Знаменатель не может быть равен нулю!" << endl;
				flag = 1;
			}
		} while (flag);
		do
		{
			flag = 0;
			cout << "Введите числитель и знаменатель второй дроби: ";
			cin >> num2 >> denom2;
			if (denom2 == 0)
			{
				cout << "Знаменатель не может быть равен нулю!" << endl;
				flag = 1;
			}
		} while (flag);
		RationalFraction frac1(num1, denom1);
		RationalFraction frac2(num2, denom2);
		RationalFraction sum = frac1 + frac2;
		RationalFraction diff = frac1 - frac2;
		RationalFraction multi = frac1 * frac2;
		RationalFraction div = frac1 / frac2;
		cout << "Сумма: ";
		sum.print();
		cout << "Разница: ";
		diff.print();
		cout << "Умножение: ";
		multi.print();
		if (num2 == 0)
			cout << "Деление: Ошибка: деление на ноль!" << endl;
		else
		{
			cout << "Деление: ";
			div.print();
		}
		cout << "Чтобы перезапустить программу введите 1: ";
		cin >> r;
	} while (r == 1);
	system("pause");
	return 0;
}