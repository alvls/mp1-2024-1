#include <iostream>
using namespace std;

class Length_C {
	double length;
	double foot() { return (3.28 * length); };
	double yard() { return (1.09 * length); };
	double arshin() { return (1.4 * length); };
	double sazhen() { return (0.468 * length); };
	double foot_p() { cout << (3.28 * length); return (3.28 * length); };
	double yard_p() { cout << (1.09 * length); return (1.09 * length); };
	double arshin_p() { cout << (1.4 * length); return (1.4 * length); };
	double sazhen_p() { cout << (0.468 * length);  return (0.468 * length); };
public:
	void set(double length_) { length = length_; }; //���������� ������� ����� � ������
	double find() { return length; }; //������ ������� ����� � ������
	double find_p() { cout << length; return length; }; //������ ������� ����� � ������, ������� �� �������
	double find(int x) { //������ ������� ����� � ������������ �������� ���������
		switch (int y = (x % 4))
		{
		case 0:
			return foot();
		case 1:
			return yard();
		case 2:
			return arshin();
		case 3:
			return sazhen();
		}
	};
	double find_p(int x) { //������ ������� ����� � ������������ �������� ���������, ������� �� �������
		switch (int y = (x % 4))
		{
		case 0:
			return foot_p();
		case 1:
			return yard_p();
		case 2:
			return arshin_p();
		case 3:
			return sazhen_p();
		}
    };
	Length_C(double length_ = 0) { length = length_; };

};

int main() {
	Length_C p(10.0); //�������� �������
	double l = p.find(); //��������� �������� �������� length � ������ � ����������
	cout << l << "\n"; //�����
	p.set(20); // ��������� �������� ����� �� 20
	double f = p.find(2); // ��������� �������� �������� length � ������� � ����������
	p.find_p(0); // ����� �������, ��������� �������� length, � ������ ������� � �����, � ������������� ��� �������� 
	cout << "\n"  << f << "\n"; // �����
	system("pause");
}