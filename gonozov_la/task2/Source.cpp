#include <iostream>
#include <clocale>
using namespace std;

class Din_array {
	size_t sz;
	double* array;
	Din_array(size_t sz_, double* pr_array) {
		sz = sz_;
		array = pr_array;
	}
public:
	Din_array(double default_, size_t sz_) {
		sz = sz_;
		array = new double[sz] {default_};
	}
	size_t find() {
		return sz;
	}
	void set_element(double element, size_t index) {
		array[index] = element;
	}
	double find_element(size_t index) {
		return array[index];
	}
	double find_min_element() {
		double minimal = array[0];
		for (size_t index{1}; index < sz; index++)
			minimal = (array[index] < minimal) ? array[index] : minimal;
		return minimal;

	}
	bool sorted_check(){
		for (size_t index{1}; index < sz; index++) {
			if (array[index] < array[index - 1]) {
				return false;
			}
		}
		return true;
	}
	Din_array create_subarray() {
		size_t ssz = sz / 2;
		double* subarray = new double[ssz];
		for (size_t index = 0; index < ssz; index++)
			subarray[index] = array[index * 2 + 1];
		return Din_array(ssz, subarray);
	}
	void output_a() {
		cout << "������ �������:" << sz <<endl;
		for (size_t index{}; index < sz; index++)
			cout << array[index]<< " ";
	}
	/*void output_sa() {
		cout << "������ ����������:" << ssz << endl;
		for (size_t index{}; index < ssz; index++)
			cout << subarray[index]<< " ";
	}*/
	~Din_array() {
		delete [] array;
		array = nullptr;
	}
};

void main() {
	setlocale(LC_ALL, "rus");
	Din_array s(0, 15); //�������� �������
	size_t t = s.find(); // ������������ �������, ������������ ������ �������
	cout << t << endl;
	s.set_element(3, 1); // �������: �� ������� 1 ������������� ������� �������� 3
	cout << s.find_element(1) << endl; 
	cout << s.find_element(0) << endl;
	cout << s.sorted_check() << endl; //�������� �� �����������������
	s.set_element(-1.25, 2); 
	cout << s.find_min_element() << endl; //���������� ������������ ��������
	Din_array c = s.create_subarray(); // �������� ���������� �� �������� ��������
	s.output_a(); // ����� ���������� � �������
	cout << "\n";
	c.output_a(); // ����� ���������� � �������
	cout << "\n";
	//s.output_sa(); // ����� ���������� � ����������
	system("pause");
}