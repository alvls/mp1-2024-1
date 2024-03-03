#include <iostream>
#include <ciso646>
#include <string>
#include <cmath>
using namespace std;
class polinom
{
	int degree;
	double* coef;
	string name;
public:
	polinom()
	{
		degree = 0;
		coef = new double;
		*coef = 0;
	}
	polinom(int degree_)
	{
		degree = degree_;
		coef = new double[degree + 1];
	}
	~polinom()
	{
		delete[] coef;
	}
	void Set_degree(int degree_)
	{
		degree = degree_;
	}
	int Get_degree()
	{
		return degree;
	}
	void Set_coef(int number, double coef_)
	{
		*(coef + number) = coef_;
		for (int i = degree; i >= 0; i--)
		{
			if (coef[i] != 0)
			{
				degree = i;
				break;
			}
		}
	}
	double Get_coef(int number)
	{
		return *(coef + number);
	}
	void Set_name(string a)
	{
		name = a;
	}
	string Get_name()
	{
		return name;
	}
	void Print()
	{
		for (int i = degree; i >= 2; i--)
		{
			if (coef[i] != 0 and coef[i] != 1)
			{
				cout << coef[i] << "x^" << i << " + ";
			}
			if (coef[i] == 1)
			{
				cout << "x^" << i << " + ";
			}
		}
		if (coef[1] != 0 and coef[1] != 1 and degree > 0)
		{
			cout << coef[1] << "x" << " + ";
		}
		if (coef[1] == 1 and degree > 0)
		{
			cout << "x" << " + ";
		}
		if (coef[0] != 0 and degree > 0)
		{
			cout << coef[0];
		}

		if (degree == 0)
		{
			cout << coef[0];
		}
		cout << endl;

	}
	double Value_at_point(double value)
	{
		double result = 0;
		for (int i = 0; i < degree + 1; i++)
		{
			result += coef[i] * pow(value, i);
		}
		return result;
	}
	void Derivative()
	{	
		if (degree == 0)
		{
			coef[0] = 0;
		}
		else
		{
			double* tmp = new double[degree + 1];
			for (int i = 0; i < degree + 1; i++)
			{
				tmp[i] = coef[i];
			}

			for (int i = degree - 1; i >= 0; i--)
			{

				coef[i] = tmp[i + 1] * (i + 1);
			}
			degree--;
			delete[] tmp;
		}
	}
};

int main()
{
	polinom A(4);
	A.Set_name("First polinom");
	A.Set_coef(0, 19.7);
	A.Set_coef(1, 46.4);
	A.Set_coef(2, 3);
	A.Set_coef(3, -100.6);
	A.Set_coef(4, 45);

	A.Print();
	A.Derivative();
	A.Print();
	
	double value = A.Value_at_point(7);

	cout << value << endl;
	cout << A.Get_coef(3) << endl;
	cin.get();
	return 0;
}