#include <iostream>
#include <cmath>
using namespace std;

class Matrix
{
	int** matr;
	int size = 0;
public:
	Matrix(int size_)
	{
		if (size_ < 2 || size_ > 8)
			size = 2;
		else
			size = size_;
		matr = new int* [size];
		for (int i = 0; i < size; i++)
			matr[i] = new int[size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = 0;
	}
	Matrix(const Matrix& copy)
	{
		size = copy.size;
		matr = new int* [size];
		for (int i = 0; i < size; i++)
			matr[i] = new int[size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = copy.matr[i][j];
	}
	void print_matrix()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				cout << matr[i][j] << '\t';
			cout << endl << endl << endl << endl;
		}
		cout << endl<< endl;
	}
	int GetSize()
	{
		return size;
	}
	void SetElement(int cols, int rows, int value)
	{
		if (cols < 1 || cols > size || rows < 1 || rows > size)
			return;
		else 
			matr[cols - 1][rows - 1] = value;
	}
	int GetElement(int cols, int rows)
	{
		if (cols < 1 || cols > size || rows < 1 || rows > size)
			return matr[0][0];
		return matr[cols - 1][rows - 1];
	}
	bool diag_predominance()
	{
		int sum;
		for (int i = 0; i < size; i++)
		{
			sum = 0;
			for (int j = 0; j < size; j++)
			{
				sum = sum + abs(matr[i][j]);
			}
			if (abs(matr[i][i]) <= sum - abs(matr[i][i]))
				return false;
		}
		return true;
	}
	void filling_rand_values()
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = rand() % 10;
	}
	void reset_values()
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = 0;
	}
	Matrix addition(const Matrix& term)
	{
		if (size != term.size)
		{
			return *this;
		}
		Matrix result(*this);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.matr[i][j] = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.matr[i][j] = this->matr[i][j] + term.matr[i][j];
		return result;
	}
	Matrix operator+(const Matrix& term)
	{
		if (this->size != term.size)
		{
			return *this;
		}
		Matrix result(*this);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.matr[i][j] = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.matr[i][j] = matr[i][j] + term.matr[i][j];
		return result;
	}
	Matrix& operator=(const Matrix& term)
	{
		if (this == &term)
			return *this;
		for (int i = 0; i < this->size; i++)
			delete[] this->matr[i];
		delete[] this->matr;
		this->size = term.size;
		matr = new int* [this->size];
		for (int i = 0; i < this->size; i++)
			matr[i] = new int[this->size];
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				this->matr[i][j] = term.matr[i][j];
		return *this;
	}
	~Matrix()
	{
		for (int i = 0; i < size; i++)
			delete[] matr[i];
		delete[] matr;
	}
};

int main()
{
	srand(time(NULL));
	//тест конструкторов + тест на поведение при неверных значениях
	Matrix ex1(4), ex2(1), ex3(9);
	ex1.print_matrix();
	ex2.print_matrix();
	ex3.print_matrix();
	//тест геттера + метод с рандом()
	ex1.filling_rand_values();
	ex1.print_matrix();
	cout <<"ex 1 size = "<< ex1.GetSize() << endl <<"ex1 elem on pos 2,3 = "<< ex1.GetElement(2, 3) << endl <<"reaction for incorrect pos is return elem on pos 1, 1 = "<< ex1.GetElement(5, 3) << endl << endl;
	//тест сеттера
	cout << "setter test" << endl << endl;
	ex1.SetElement(2, 2, 100);
	ex1.print_matrix();
	//тест сложения в нескольких вариантах
	cout << "addition test" << endl << endl;
	Matrix term1(3), term2(3), term_incorrect(4), result(6);//показано, что будет, если сложить матрицы разных размеров + тест перегрузки присваивания
	term1.filling_rand_values();
	term2.filling_rand_values();
	term_incorrect.filling_rand_values();
	term1.print_matrix();
	term2.print_matrix();
	result = term1 + term2;
	result.print_matrix();
	cout << "reaction on incorrect addition, lhf was returned" << endl << endl;
	result = term1 + term_incorrect;
	result.print_matrix();
	//это диагональное преобладание
	cout << "diag_predominance test" << endl << endl;
	Matrix test(3);
	for (int flag = 0; flag == 0;)
	{
		test.filling_rand_values();
		if (test.diag_predominance() == true)
			flag = 1;
	}
	cout << "true: " << endl;
	test.print_matrix();
	for (int flag = 0; flag == 0;)
	{
		test.filling_rand_values();
		if (test.diag_predominance() == false)
			flag = 1;
	}
	cout << "false: " << endl;
	test.print_matrix();
	system("pause");
}