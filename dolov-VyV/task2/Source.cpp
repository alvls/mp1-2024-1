#include <iostream>
#include <locale.h>

class Polynomial {
private:
	static const int MX_DGR = 12;
	int coeff[MX_DGR + 1];
	int degree;

public:
	Polynomial() : degree(0)
	{
		for (int i = 0; i <= MX_DGR; i++) {
			coeff[i] = 0;
		}
	}

	void setDegree(int new_deg)
	{
		if ((new_deg <= MX_DGR) && (new_deg >= 0))
		{
			degree = new_deg;
			for (int i = degree + 1; i <= MX_DGR; i++) {
				coeff[i] = 0;
			}
		}
		else {
			std::cout << "Степень выходит за пределы допустимого диапазона!"  << std::endl;
		}
	}

	void setCoefficient(int index, int val) {
		coeff[index] = val;
	}

	int getDegree() {
		return degree;
	}

	int getCoefficient(int index) {
		return coeff[index];
	}

	double value(double x) {
		double res = 0;
		for (int i = degree; i >= 0; i--) {
			double a = 1;
			for (int j = 0; j < i; j++) {
				a *= x;
			}
			res += coeff[i] * a;
		}
		return res;
	}

	Polynomial derivative() {
		Polynomial der_pol;
		if (degree >= 1) {
			der_pol.setDegree(degree - 1);
			for (int i = 1; i <= degree; i++) {
				der_pol.setCoefficient(i - 1, i * coeff[i]);
			}
		}
		return der_pol;
	}

	void print() {
		bool flag = true;
		for (int i = degree; i >= 0; i--) {
			if (coeff[i] == 0) 
				continue;

			if (!flag) {
				if (coeff[i] > 0)
					std::cout << " + ";
				else
					std::cout << " - ";
			}
			else {
				if (coeff[i] < 0) 
					std::cout << "-";
				flag = false;
			}
			if ((abs(coeff[i]) != 1) || (i == 0))
				std::cout << abs(coeff[i]);
			if (i != 0) {
				std::cout << "x";
				if (i > 1) 
					std::cout << "^" << i;
			}
		}
		std::cout << "\n";
	}

	~Polynomial() {}
};

int main() {
	setlocale(LC_ALL, "rus");
	Polynomial p;
	p.setDegree(3);
	p.setCoefficient(0, 3);
	p.setCoefficient(1, -2);
	p.setCoefficient(2, 1);
	p.setCoefficient(3, -4);

	std::cout << "Полином: ";
	p.print();
	std::cout << "Степень полинома: " << p.getDegree() << std::endl;
	int index = 1;
	std::cout << "Коэффициент при x^" << index << ": " << p.getCoefficient(index) << std::endl;

	Polynomial derivative = p.derivative();
	std::cout << "Производная: ";
	derivative.print();

	int val = 2;
	std::cout << "Значение при x = " << val << ": " << p.value(val) << std::endl;

	std::cin.get();
	return 0;
}