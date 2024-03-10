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
	Matrix(int size_ = 2) { // ����������� ��� ������� ������� ������� ��������
		size = size_;
		m = new int* [size];
		for (int i = 0; i < size; i++)
			m[i] = new int[size];
	}

	Matrix(const vector<int>& v) { // ����������� ��� ������� ������� ������� �������� ��������
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

	Matrix(const Matrix& p) { // ����������� ����������� 
		size = p.size;
		m = new int* [size];
		for (int i = 0; i < size; i++) {
			m[i] = new int[size];
			for (int j = 0; j < size; j++) {
				m[i][j] = p.m[i][j];
			}
		}
	}

	void setSize(int size_) // ������ ������ �������
	{
		if (2 <= size_ && size_ <= 8)
		{
			size = size_;
			m = new int* [size];
			for (int i = 0; i < size; i++)
				m[i] = new int[size];
		}
	}

	int getSize() { return size; } // ������ ������ �������

	void setElement(int row, int col, int value) { // ������ ������� ������� �� ��������
		if (row >= 0 && row < size && col >= 0 && col < size)
			m[row][col] = value;
	}

	int getElement(int row, int col) { // ������ ������� �� ��������
			return m[row][col];
	}

	void print() { // ������� �������
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				cout << m[i][j] << ' ';
			cout << '\n';
		}
	}

	Matrix operator + (const Matrix& p) { // �������� ������
		Matrix result(size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.m[i][j] = m[i][j] + p.m[i][j];
		return result;
	}

	Matrix operator - (const Matrix& p) { // ��������� ������
		Matrix result(size);
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				result.m[i][j] = m[i][j] - p.m[i][j];
		return result;
	}

	Matrix& operator = (const Matrix& p) { // ������������� ������ 
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

	bool isDiagPr() { // �������� �� ������������ ������������
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

	long long determinant(int size_) { // ����������� ������� ����� ���������� ������ ������
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
	// ������ ������ ���������

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
			10, 10, 10, 14, 7, 2, 3, 16, 5, 5, 11, 1, 20, 17, 8, 18, 16 }); // ������� 6x6
	g.print();
	cout << '\n' << g.determinant(g.getSize()) << '\n';

	system("pause");
}

