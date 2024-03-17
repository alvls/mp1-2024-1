//Класс должен содержать необходимые служебные методы(конструкторы, деструктор и пр.).
//Класс должен предоставлять следующие операции :
//1) задать текущую функцию,
//2) задать пределы интегрирования,
//3) узнать пределы интегрирования,
//4) задать число отрезков метода прямоугольников,
//5) выбрать метод вычисления,
//6) вычислить значение интеграла выбранным методом,
//7) вывести результат вычисления на экран.



#include <iostream> 
#include <cmath>
#include <string>
using namespace std;

typedef double(*cmath_function)(double x);
class integral_calculator
{
private:
	cmath_function f;
	double sum;
	double left_size;
	double right_size;
	int num_of_segments;
	int method; // 0 - left rectangle method, 1 - right rectangle method, 2 - middle rectangle method
	string name;
public:
	integral_calculator() // default constructor
	{
		f = sin;
		left_size = 0;
		right_size = 1;
		num_of_segments = 100;
		method = 0;
	}
	integral_calculator(cmath_function f,const double& left_size, const double& right_size,const int& num_of_segments,const int& method)
	{	
		this->f = f;
		this->left_size = left_size;
		this->right_size = right_size;
		this->num_of_segments = num_of_segments;
		this->method = method;
	}
	double calculate()
	{	
		sum = 0;
		double x;
		double length = (right_size - left_size) / num_of_segments;
		if (method == 0)
		{
			for (int i = 0; i < num_of_segments; i++)
			{
				x = left_size + i * length;
				sum += f(x) * length;
			}
		}
		if (method == 1)
		{
			for (int i = 1; i <= num_of_segments; i++)
			{
				x = left_size + i * length;
				sum += f(x) * length;
			}
		}
		if (method == 2)
		{
			for (int i = 0; i < num_of_segments; i++)
			{
				x = left_size + (i + 0.5) * length;
				sum += f(x) * length;
			}
		}
		return sum;
	}
	void set_size(const double& left_size, const double& right_size)
	{
		this->left_size = left_size;
		this->right_size = right_size;
	}
	double& get_left_size()
	{
		return left_size;
	}
	double& get_right_size()
	{
		return right_size;
	}
	void set_num_of_segments(const int& num_of_segments)
	{
		this->num_of_segments = num_of_segments;
	}
	int& get_num_of_segments()
	{
		return num_of_segments;
	}
	void set_function(cmath_function f)
	{
		this->f = f;
	}
	void set_method(const int& method)
	{
		this->method = method;
	}
	int& get_method()
	{
		return method;
	}
	friend ostream& operator<<(ostream& os, const integral_calculator& integral)
	{
		os << "Integral on " << "[" << integral.left_size<< ";" << integral.right_size << "] equals " << integral.sum;
		return os;
	}
};


int main()
{
	integral_calculator a(cos, 0, 1, 10000, 0);
	a.calculate();
	cout << a << endl;

	a.set_function(sqrt);
	a.set_size(1, 4);
	a.calculate();
	cout << a << endl;

	cin.get();


	return 0;
}