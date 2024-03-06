#include <iostream>
#include <math.h>

using namespace std;

class Matrix {
	int dimension;
	long long** matr;
public:
	Matrix(int dimension_) {
		dimension = dimension_;
		matr = new long long* [dimension];
		for (int i = 0; i < dimension; i++) {
			matr[i] = new long long[dimension];
		}
	}
	Matrix(const Matrix&  m) {
		dimension = m.dimension;
		matr = new long long* [dimension];
		for (int i = 0; i < dimension; i++) {
			matr[i] = new long long[dimension];
			for (int j = 0; j < dimension; j++) {
				matr[i][j] = m.matr[i][j];
			}
		}
	}
	Matrix() {};
	void setDimension(int dim) {
		if (2 <= dim && dim <= 8) {
			matr = new long long* [dim];
			dimension = dim;
			for (int i = 0; i < dim; i++) {
				matr[i] = new long long[dim];
			}
		}
	}
	int getDimension() {
		return dimension;
	}
	void setElement(int x, int y, int element) {
		matr[x][y] = element;
	}
	long long getElement(int x, int y) {
		return matr[x][y];
	}
	bool diagdom() {
		bool ans = 1;
		for (int i = 0; i < dimension; i++) {
			long long teksum = 0;
			for (int j = 0; j < dimension; j++) {
				teksum += abs(matr[i][j]);
			}
			teksum -= abs(matr[i][i]);
			if (abs(matr[i][i]) < teksum) {
				ans = 0;
				break;
			}
		}
		return ans;
	}
	Matrix operator+(const Matrix&  m1) {
		Matrix mres(dimension);
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				mres.matr[i][j] = this->matr[i][j] + m1.matr[i][j];
			}
		}
		return mres;
	}
	Matrix& operator=(const Matrix& m1) {
		dimension = m1.dimension;
		matr = new long long* [dimension];
		for (int i = 0; i < dimension; i++) {
			matr[i] = new long long[dimension];
			for (int j = 0; j < dimension; j++) {
				matr[i][j] = m1.matr[i][j];
			}
		}
		return *this;
	}
	Matrix& operator+=(const Matrix& m1) {
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				matr[i][j] += m1.matr[i][j];
			}
		}
		return *this;
	}
	void print() {
		for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				cout << matr[i][j] << " ";
			}
			cout << endl;
		}
	}
	~Matrix() {
		for (int i = 0; i < dimension; i++) {
			delete[] matr[i];
		}
		delete [] matr;
	}
};

int main() {
	int n = 3;
	long long mat1[3][3] = { {4, 1, 2}, {8, 17, 7}, {9, 0, 14} }, mat2[3][3] = { {0, 1, 0}, {1, 2, 2}, {3, 2, 8} };
	Matrix m1(n), m2(2);
	cout << "Dimension of m2: " << m2.getDimension() << endl;

	int pow2 = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			m2.setElement(i, j, pow(2, pow2++));
		}
	}

	cout << "m2:" << endl;
	m2.print();
	cout << "m2[1][0] = " << m2.getElement(1, 0) << endl;
	m2.setElement(1, 0, 56);
	cout << "Set value of m2[1][0] to 56\n" << "m2[1][0] = " << m2.getElement(1, 0) << endl;

	m2.setDimension(3);
	cout << "Set dimension of m2 to 3 and re-set its elements" << endl;
	for (long long i = 0; i < n; i++) {
		for (long long j = 0; j < n; j++) {
			m1.setElement(i, j, mat1[i][j]);
			m2.setElement(i, j, mat2[i][j]);
		}
	}

	cout << "m1:" << endl;
	m1.print();
	cout << "m2:" << endl;
	m2.print();

	cout << "Is m1 diagonally dominant: " << m1.diagdom() << endl;
	cout << "Is m2 diagonally dominant: " << m2.diagdom() << endl;
	
	Matrix m3 = m1 + m2;
	cout << "m3 is a result of summing m1 and m2 \nm3:" << endl;
	m3.print();
	cout << "Is m3 diagonally dominant: " << m3.diagdom() << endl;
	Matrix s;
	system("pause");
	return 0;
}