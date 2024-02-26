#include <iostream>
#include <locale.h>

class Rational {
private:
	int num;
	int denom;

	int gcd(int a, int b) const {
		while (b != 0) {
			int temp = a % b;
			a = b;
			b = temp;
		}
		return a;
	}

	void reduce() {
		int g = gcd(num, denom);
		num /= g;
		denom /= g;
		if (denom < 0) {
			num = -num;
			denom = -denom;
		}
	}

public:
	Rational(int numerator = 0, int denominator = 1) {
		num = numerator;
		denom = denominator;
		reduce();
	}

	Rational add(const Rational& oth) {
		int commondenom = denom * oth.denom;
		int newnum = num * oth.denom + oth.num * denom;
		Rational result(newnum, commondenom);
		return result;
	}
	Rational subtract(const Rational& oth) {
		int commondenom = denom * oth.denom;
		int newnum = num * oth.denom - oth.num * denom;
		Rational result(newnum, commondenom);
		return result;
	}

	Rational multiply(const Rational& oth) {
		int newnum = num * oth.num;
		int commondenom = denom * oth.denom;
		Rational result(newnum, commondenom);
		return result;
	}

	Rational divide(const Rational& oth) {
		int newnum = num * oth.denom;
		int commondenom = denom * oth.num;
		Rational result(newnum, commondenom);
		return result;
	}

	void pr() {
		if (denom == 1) {
			std::cout << num << '\n';
		}
		else {
			std::cout << num << '/' << denom << '\n';
		}
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	Rational r1(1, 2), r2(4, 5);

	Rational sum = r1.add(r2);
	std::cout << "Сумма: ";
	sum.pr();

	Rational difference = r1.subtract(r2);
	std::cout << "Разность: ";
	difference.pr();

	Rational product = r1.multiply(r2);
	std::cout << "Произведение: ";
	product.pr();

	Rational quotient = r1.divide(r2);
	std::cout << "Частное: ";
	quotient.pr();

	std::cin.get();
	return 0;
}