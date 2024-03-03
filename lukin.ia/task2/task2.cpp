#include <iostream>
#include <cmath>
using namespace std;

class Matrix
{
	int** matr;
	int size = 0;
public:
	Matrix()
	{
		cout << "Please, enter the matrix size! It must be 2-8!" << endl;
		for (int flag = 0; flag == 0;)
		{
			cin >> size;
			if (size < 2 || size > 8)
				cout << "Incorrect size!See the instructions!" << endl;
			else 
				flag = 1;
		}
		cout << endl;
		matr = new int* [size];
		for (int i = 0; i < size; i++)
			matr[i] = new int[size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				matr[i][j] = 0;
	}
	Matrix(int size_)
	{ 
		if (size_ < 2 || size_ > 8)
		{
			cout << "Incorrect size!Enter size manually!It must be 2-8!" << endl;
			for (int i = 0; i == 0;)
			{
				cin >> size_;
				if (size_ < 2 || size_ > 8)
					cout << "Incorrect size!See the instructions!" << endl;
				else i = 1;
			}
		}
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
		cout << "Your matrix:" << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				cout << matr[i][j] << '\t';
			cout << endl<<endl<<endl<<endl;
		}
		cout << endl << endl;
	}
	int GetSize()
	{
		return size;
	}
	void SetElement()
	{
		int i, j, value;
		print_matrix();
		cout << "Please, enter the indexes of the elememt, that you want to set!" << endl;
		for (int flag = 0; flag == 0;)
		{
			cin >> i >> j;
			if (i<1 || i>size || j<1 || j>size)
				cout << "Incorrect indexes. Check the size!" << endl;
			else
				flag = 1;
		}
		i = i - 1;
		j = j - 1;
		cout << "Now, enter the value of the element!" << endl;
		cin >> value;
		matr[i][j] = value;
	}
	int GetElement()
	{
		int i, j;
		cout << "Please, enter the indexes of the elememt, that you want to get!" << endl;
		cin >> i >> j;
		return matr[i][j];
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
			cout << "The matrix sizes must be equal! The original matrix was returned" << endl;
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
			cout << "The matrix sizes must be equal! The left matrix was returned" << endl;
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
	Matrix& operator=(const Matrix& term)//это написал, чтобы сложение нормально работало
	{
		if (this == &term)
			return *this;
		for (int i = 0; i < this->size; i++)
			delete[] this->matr[i];
		delete[] this->matr;
		this->size = term.size;//по-хорошему здесь надо проверять, выделилась ли память, но так как есть проверки на корректный размер, то вроде всегда будет правильно выделяться
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
	//тест всех конструкторов, ех4 показывает реакцию конструктора на неверные параметры.
	Matrix ex1;
	ex1.filling_rand_values();
	ex1.print_matrix();
	Matrix ex2(5), ex3(ex1), ex4(1);
	cout << "This is the ex3 - copy of ex1" << endl;
	ex3.print_matrix();
	//тест геттера и сеттера
	cout <<"ex1 size is: " << ex1.GetSize() << endl<<endl;
	ex1.SetElement();
	ex1.print_matrix();
	//тест опрератора сложения + присваивания
	Matrix term1(3), term2(3), term_incorrect(4), result(6);
	term1.filling_rand_values();
	term2.filling_rand_values();
	term_incorrect.filling_rand_values();
	term1.print_matrix();
	term2.print_matrix();
	result = term1 + term2;
	result.print_matrix();
	result = term1 + term_incorrect;
	result.print_matrix();
	//тест диаг. преобладания
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