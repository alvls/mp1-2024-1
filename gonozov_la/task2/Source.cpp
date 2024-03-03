#include <iostream>
using namespace std;

class Din_array {
	size_t sz;
	double* array;
	size_t ssz;
	double* subarray = new double[1];
public:
	Din_array(size_t sz_, double default_) {
		sz = sz_;
		array = new double[sz] {default_};
	}
	size_t find() {
		return sz;
	}
	void set_elem(double element, size_t index) {
		array[index] = element;
	}
	double find_element(size_t index) {
		return array[index];
	}
	double find_min_element() {
		double minimal{ array[0] };
		for (size_t index{1}; index < sz; index++)
			minimal = (array[index] < minimal) ? array[index] : minimal;

	}
	bool sorted_check(){
		for (size_t index{1}; index < sz; index++) {
			if (array[index] < array[index - 1]) {
				return false;
			}
		}
		return true;
	}
	void create_subarray() {
		ssz = (sz % 2 == 0) ? sz / 2 : sz / 2 + 1;
		delete[] subarray;
		subarray = new double[ssz];
		for (size_t index{}; index < ssz; index++)
			subarray[index] = array[index * 2 + 1];
	}
	void output_a() {
		cout << "Размер массива:" << sz <<endl;
		for (size_t index{}; index < sz; index++)
			cout << array[index];
	}
	void output_sa() {
		cout << "Размер подмассива:" << sz << endl;
		for (size_t index{}; index < ssz; index++)
			cout << subarray[index];
	}
	~Din_array() {
		delete [] array;
		delete [] subarray;
		array = nullptr;
		subarray = nullptr;
	}
};