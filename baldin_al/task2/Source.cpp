#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Matrix
{
private:
	int size;
	int** m;

public:
	Matrix(int size_ = 0) { // конструктор для матрицы которая задаётся размером
		size = size_;
		m = new int* [size];
		for (int i = 0; i < size; i++)
			m[i] = new int[size];
	}

	Matrix(const vector<int>& v) { // конструктор для матрицы которая задаётся вектором значений
		int count = v.size();
		size = ceil(sqrt(count));
		m = new int* [size];
		for (int i = 0; i < size; i++) {
			m[i] = new int[size];
		}
		int index = 0;
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				if (index < count)
					m[i][j] = v[index++];
				else
					m[i][j] = 0;
			}
	}

	Matrix(const Matrix& p) { // конструктор копирования 
		size = p.size;
		m = new int* [size];
		for (int i = 0; i < size; i++) {
			m[i] = new int[size];
			for (int j = 0; j < size; j++) {
				m[i][j] = p.m[i][j];
			}
		}
	}

	void setSize(int size_ = 0) // задать размер матрицы
	{
		size = size_;
		if (size < 2 || size > 8)
			cout << "The dimension of matrix should be from 2 to 8" << '\n';
		else {
			m = new int* [size];
			for (int i = 0; i < size; i++)
				m[i] = new int[size];
		}
	}

	int getSize() { return size; } // узнать размер матрицы

	void setElement(int row, int col, int value) { // задать элемент матрицы по индексам
		if (row >= 0 && row < size && col >= 0 && col < size)
			m[row][col] = value;
		else
			cout << "Invalid indexes" << '\n';
	}

	int getElement(int row, int col) { // узнать элемент по индексам
		if (row >= 0 && row < size && col >= 0 && col < size)
			return m[row][col];
		cout << "Invalid indexes" << ' ';
		return -1;
	}

	void print() { // вывести матрицу
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				cout << m[i][j] << ' ';
			cout << '\n';
		}
	}

	Matrix operator + (const Matrix& p) { // сложение матриц
		Matrix result(size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.m[i][j] = m[i][j] + p.m[i][j];
		return result;
	}

	Matrix operator - (const Matrix& p) { // вычитание матриц
		Matrix result(size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.m[i][j] = m[i][j] - p.m[i][j];
		return result;
	}

	Matrix& operator = (const Matrix& p) { // приравнивание матриц 
		if (this == &p)
			return *this;

		for (int i = 0; i < size; i++)
			delete m[i];
		delete m;

		size = p.size;
		m = new int* [size];
		for (int i = 0; i < size; i++)
			m[i] = new int[size];
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				m[i][j] = p.m[i][j];

		return *this;
	}

	bool isDiagPr() { // проверка на диагональное преобладание
		if (size == 0) {
			cout << "Matrix hasn't initialized yet" << ' ';
			return 0;
		}
		else {
			long long sum = 0;
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i != j)
						sum += abs(m[i][j]);
			for (int i = 0; i < size; i++)
				if (abs(m[i][i]) < sum)
					return 0;
			return 1;
		}
	}

	long long determinant(int size_) { // детерминант матрицы через разложение первой строки
		long long det = 0;
		int sign = 1;

		if (size == 2)
			return m[0][0] * m[1][1] - m[0][1] * m[1][0];

		for (int j = 0; j < size; j++) {
			Matrix subm(size - 1);
			int subj = j;
			int id1 = 0;
			int id2 = 0;
			for (int i = 0; i < size; i++) {
				for (int k = 0; k < size; k++) {
					if (i == 0 || k == subj) continue;
					if (id2 >= size - 1) {
						id1++;
						id2 = 0;
					}
					subm.setElement(id1, id2, m[i][k]);
					id2++;
				}
			}
			det += sign * m[0][j] * subm.determinant(size - 1);
			sign = -sign;
		}

		return det;
	}


	~Matrix() {
		for (int i = 0; i < size; i++)
			delete[] m[i];
		delete[] m;
	}


};
int main()
{
	// пример работы программы

	Matrix a, b(8), c({ 1, 2, 3, 4, 5, 6, 7 });

	a.setSize(3);
	cout << b.getSize() << '\n';

	c.setElement(2, 1, 8);
	c.setElement(2, 2, 9);
	c.print();

	cout << c.getElement(0, 0) << '\n';

	if (c.isDiagPr())
		cout << "+" << '\n';
	else
		cout << "-" << '\n';

	Matrix d({ -8, 3, 1, 10 }), e({ 9, 8, 6, -3 });

	if (d.isDiagPr())
		cout << "+" << '\n';
	else
		cout << "-" << '\n';

	cout << '\n';
	d.print();
	cout << '\n';
	e.print();
	cout << '\n';
	Matrix f = d + e;
	f.print();
	f = f - e;
	f = f;
	cout << '\n';
	f.print();

	cout << '\n';
	Matrix g({ 14, 14, 1, 19, 16, 12, 8, 7, 13, 11, 12, 19, 14, 19, 20, 18, 14, 16, 9,
			10, 10, 10, 14, 7, 2, 3, 16, 5, 5, 11, 1, 20, 17, 8, 18, 16 }); // матрица 6x6
	g.print();
	cout << '\n' << g.determinant(g.getSize()) << '\n';

	system("pause");
}

