#include<iostream>
using namespace std;

class Dynamic {
	double* mdata;
	size_t msize;
public:
	Dynamic(size_t size = 0) {
		msize = size;
		mdata = new double[size];
	}
	void setsize(size_t size) {
		msize = size;
		delete[] mdata;
		mdata = new double[size];
	}
	size_t size() {
		return msize;
	}
	void set(size_t index, double value) {
		mdata[index] = value;
	}
	double get(size_t index) {
		return mdata[index];
	}
	void print() {
		for (size_t i = 0; i < msize; i++) {
			cout << mdata[i] << ' ';
		}
		cout << endl;
	}
};

int main() {
	Dynamic a(10);
	a.set(1, 42);
	a.set(5, 999);
	a.print();
}