#include <iostream>
#include <locale.h>
#include <string>
#include <stdexcept>

class IntegralCalculator {
public:
	typedef double(*Function)(double);

private:
	Function func;
	double low_bound;
	double up_bound;
	int num;
	int method;

	static const int left = 0;
	static const int right = 1;
	static const int middle = 2;

	double calculateLeft() {
		double step = (up_bound - low_bound) / num;
		double sum = 0;
		for (int i = 0; i < num; i++) {
			sum += func(low_bound + i * step) * step;
		}
		return sum;
	}

	double calculateRight() {
		double step = (up_bound - low_bound) / num;
		double sum = 0;
		for (int i = 1; i <= num; i++) {
			sum += func(low_bound + i * step) * step;
		}
		return sum;
	}

	double calculateMiddle() {
		double step = (up_bound - low_bound) / num;
		double sum = 0;
		for (int i = 0; i < num; i++) {
			sum += func(low_bound + (i + 0.5) * step) * step;
		}
		return sum;
	}

public:
	IntegralCalculator(Function f = 0, double lower = 0, double upper = 1, int segments = 100, int mthd = middle)
	{
		if(segments <= 0)
			throw std::invalid_argument("���������� �������� ������ ���� ������ 0");
		if (upper <= lower)
			throw std::invalid_argument("������� ������ ������ ���� ������ ������� �������");

		func = f;
		low_bound = lower;
		up_bound = upper;
		num = segments;
		method = mthd;
	}

	void setFunction(Function f) {
		func = f;
	}

	void setBounds(double lower, double upper) {
		low_bound = lower;
		up_bound = upper;
	}

	void getBounds(double& lower, double& upper) const {
		lower = low_bound;
		upper = up_bound;
	}

	void setNumSegments(int n) {
		num = n;
	}

	void setMethod(const std::string& method_name) {
		if (method_name == "left") {
			method = left;
		}
		else if (method_name == "right") {
			method = right;
		}
		else if (method_name == "middle") {
			method = middle;
		}
		else {
			throw std::invalid_argument("����������� ����� ���������� ");
		}
	}

	double calculate() {
		if (!func) {
			throw std::invalid_argument("������� ��� ���������� ��������� �� ����������� ");
		}
		switch (method) {
		case left:
			return calculateLeft();
		case right:
			return calculateRight();
		case middle:
			return calculateMiddle();
		default:
			throw std::invalid_argument("����������� ����� ���������� ");
		}
	}

	void printResult() {
		std::cout << "��������������� �������� ���������: " << calculate() << std::endl;
	}

	~IntegralCalculator() {}
};

double squareFunction(double x) {
	return x * x;
}

int main() {
	try {
		setlocale(LC_ALL, "rus");
		IntegralCalculator calc;
		calc.setFunction(squareFunction);
		calc.setBounds(0, 1);
		calc.setNumSegments(100);
		calc.setMethod("middle");

		double lowerBound, upperBound;
		calc.getBounds(lowerBound, upperBound);
		std::cout << "������ ������ ��������������: " << lowerBound << std::endl;
		std::cout << "������� ������ ��������������: " << upperBound << std::endl;
		calc.printResult();
	}
	catch (const std::exception & e) {
		std::cerr << "��������� ����������: " << e.what() << std::endl;
	}
	std::cin.get();
	return 0;
}
