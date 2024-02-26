#include<iostream>
using namespace std;

//project from vs2022 not working((((((
class Dynamic {
	double* mdata;
	size_t msize;

public:
	Dynamic(size_t size = 0) { //ислледовать, что будет если оставить пустым
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
		cout << "{ ";
		for (size_t i = 0; i < msize; i++) {
			cout << mdata[i] << ' ';
		}
		cout <<'}'<< endl;
	}

	size_t findmin() {
		double mi = INFINITY;
		size_t index = 0;
		for (size_t i = 0; i < msize; i++) {
			if (mdata[i] < mi) {
				index = i;
				mi = mdata[i];
			}
		}
		return index;

	}

	bool isSorted() {//ne proveril
		for (size_t i = 1; i < msize; i++) {
			if (mdata[i] , mdata[i-1]) {
				return 0;
			}
		}
		return 1;
	}

};

int main() {
	Dynamic a(10);
	a.set(1, 42);
	a.set(5, 999);
	a.set(8, -0.5);
	a.print();
	cout << a.get(a.findmin());
}