#include <iostream>
#include <clocale>
#include <string>
#include <map>
#include <ctime>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
using namespace std;
#define ARRAY_SIZE 10.

class Processing_center {
private:
	string* salary_account = new string[ARRAY_SIZE]; //���������� �����
	unsigned actual_number; //���������� ���������� ������
	unsigned find_number; //������ ������ ����������� �����, ������������ ��� �������� �������� �����������
	string* FIO = new string[ARRAY_SIZE]; //���
	string* information_of_deposit = new string[ARRAY_SIZE];
	unsigned long* amount_account = new unsigned long[ARRAY_SIZE]; //����� �� ���������� �����
	string* password = new std::string[ARRAY_SIZE];
	bool check = false;
public:
	Processing_center() {
		//����� ������ ����������� ��������� � �������, ������� �� � ��������� ���������� ��� ������������ ��������
		//� ������ ���������� � ������ �������� ��������
		salary_account[0] = "1325"; salary_account[1] = "2356"; salary_account[2] = "7685";
		amount_account[0] = 35900; amount_account[2] = 500002; amount_account[2] = 3101786;
		FIO[0] = "������ ������� �������������"; FIO[1] = "������������ ������� ������������"; FIO[2] = "������ �������� ��������";
		password[0] = "r4t5e3"; password[1] = "asdfgh"; password[2] = "0o0o0o0o";
		actual_number = 3;
	}
	unsigned long get_amount(string salary_account_enter) {
		return amount_account[find_number];
	}
	void change_amount(unsigned long amount_account_enter) {
		amount_account[find_number] = amount_account_enter;
	}
	void sum_amount(unsigned long amount_account_enter) {
		amount_account[find_number] += amount_account_enter;
	}
	bool check_authoriz(string salary_account_enter, string password_enter) {
		if (password_enter.size() < 4) {
			check = false;
			return false;
		}
		int target = stoi(salary_account_enter);
		int i = (actual_number + 1) / 2;
		int counter = 0;
		while (target != stoi(salary_account[i])) {
			if (stoi(salary_account[i]) > target) {
				i /= 2;
				counter++;
			}
			else if (stoi(salary_account[i]) < target) {
				i += i / 2;
				counter++;
			}
			if (counter == 15) {
				check = false;
				return false;
			}
		}
		if (password[i] == password_enter && salary_account[i] == salary_account_enter) {
			find_number = i;
			check = true;
			return true;
		}
		else {
			check = false;
			return false;
		}
	}
};

class Deposit  {
	string salary_account_recieved; //���������� �� ������������� ������ ���������� ����
	unsigned long amount_account_recieved; //���������� �� ������������� ������ ����� �� ���������� �����
	bool authorization_status = false;
	string* salary_account = new string[ARRAY_SIZE];
	unsigned long* amount_deposit = new unsigned long[ARRAY_SIZE];
	unsigned long* amount_percent = new unsigned long[ARRAY_SIZE];
	time_t* t = new time_t[ARRAY_SIZE];
	unsigned* period_deposit = new unsigned[ARRAY_SIZE];
	unsigned current_position; //������� ���������� ������������ ��������
	size_t size_arrays = ARRAY_SIZE;
	Processing_center& proc_center;
public:
	Deposit(Processing_center& proc_center_): proc_center (proc_center_)
	{
		//����� ������ ����������� ��������� � �������, ������� �� � ��������� ���������� ��� ������������ ��������
		//� ������ ���������� � ������ �������� ��������
		salary_account[0] = "1325"; amount_deposit[0] = 300000; amount_percent[0] = 3000;
		t[0] = time(nullptr); period_deposit[0] = 12;
		current_position = 0; 

	}
	bool authorization(string salary_account_enter, string password_enter) {
		if (proc_center.check_authoriz(salary_account_enter, password_enter) == true) {
			salary_account_recieved = salary_account_enter;
			amount_account_recieved = proc_center.get_amount(salary_account_enter);
			authorization_status = true;

		}
		else {
			authorization_status = false;
		}
		return authorization_status;
	}
	void get_information_about_deposits() {
		if (authorization_status == true) {
			cout << "��� ��������:" << endl;
			if (amount_account_recieved > 0) {
				cout << "������� �� 3 ������, 6 �������, 1, 2 ��� 3 ���� � ���������� ������� 8% �������\n �� �����  �� 100 ���. ������" << endl;
			}
			if (amount_account_recieved >= 100000) {
				cout << "������� �� 3 ������, 6 �������, 1, 2 ��� 3 ���� � ���������� ������� 10% �������\n �� ����� �� 100 �� 500 ���. ������" << endl;
			}
			if (amount_account_recieved >= 500000) {
				cout << "������� �� 3 ������, 6 �������, 1, 2 ��� 3 ���� � ���������� ������� 14% �������\n �� ����� �� 500 ���. �� 1 ��� ������" << endl;
			}
			if (amount_account_recieved >= 1000000) {
				cout << "������� �� 3 ������, 6 �������, 1, 2 ��� 3 ���� � ���������� ������� 16% �������\n �� ����� ����� 1 ��� ������" << endl;
			}
		}
		else {
			cout << "�������� �����������" << endl;
		}
	}
	bool check_deposit() {//��������� ������� ��������� ��������
		if (authorization_status == true) {
			for (unsigned i = 0; i <= current_position; i++) {
				if (salary_account_recieved == salary_account[i]) {
					return true;
				}
			}
			return false;
		}
		else {
			cout << "�������� �����������" << endl;
			return false;
		}
	}
	bool open_deposit(unsigned long amount_account_enter, unsigned period_deposit_enter) { //���� �� ����� ������ ����� ��������� ��������� � �� �������
		if (authorization_status == true) {
			if (amount_account_enter > amount_account_recieved) {
				cout << "������� ����������� ������� �����" << endl;
				return false;
			}
			else if (period_deposit_enter == 3 || period_deposit_enter == 6 || period_deposit_enter == 12 || period_deposit_enter == 24 || period_deposit_enter == 36) {
				amount_account_recieved -= amount_account_enter;
				proc_center.change_amount(amount_account_recieved);
				if (current_position != 0) {
					current_position++;
				}
				if (current_position > size_arrays) {
					//���������� ����������� �� ���������� ������������� �������
					size_t sz_array_help = size_arrays * 2;
					string* salary_account_help = new string[sz_array_help];
					unsigned long* amount_deposit_help = new unsigned long[sz_array_help];
					unsigned long* amount_percent_help = new unsigned long[sz_array_help];
					time_t* t_help = new time_t[sz_array_help];
					unsigned* period_deposit_help = new unsigned[ARRAY_SIZE];
					for (int i = 0; i <= current_position; i++) {
						salary_account_help[i] = salary_account[i];
						amount_deposit_help[i] = amount_deposit[i];
						amount_percent_help[i] = amount_percent[i];
						t_help[i] = t[i];
						period_deposit_help[i] = period_deposit[i];
					}
					delete[] salary_account;
					delete[] amount_deposit;
					delete[] amount_percent;
					delete[] t;
					delete[] period_deposit;
					salary_account = salary_account_help;
					amount_deposit = amount_deposit_help;
					amount_percent = amount_percent_help;
					t = t_help;
					period_deposit = period_deposit_help;
					size_arrays = sz_array_help;

					/*string* salary_account = new string[10];
	unsigned long* amount_deposit = new unsigned long[10];
	unsigned long* amount_percent = new unsigned long[10];
	time_t* t = new time_t[10];
	unsigned* period_deposit = new unsigned[10];*/
				}
				salary_account[current_position] = salary_account_recieved;
				amount_deposit[current_position] = amount_account_enter;
				amount_percent[current_position] = 0;
				t[current_position] = time(nullptr);
				period_deposit[current_position] = period_deposit_enter;
			}
			else {
				cout << "������� ���������� �������, �� ������� ������ ������� ������" << endl;
				return false;
			}
		}
		else {
			cout << "�������� �����������" << endl;
			return false;
		}
		return true;
	}
	void check_status_deposit() {
		if (authorization_status == true) {
			unsigned find_number;
			bool flug = false;
			for (unsigned i = 0; i <= current_position; i++) {
				if (salary_account_recieved == salary_account[i]) {
					find_number = i;
					flug = true;
					break;
				}
			}
			if (flug == true) {
				cout << "��������� ����� ��������: " << amount_deposit[find_number] << endl;
				cout << "����������� �������: " << amount_percent[find_number] << endl;
				tm* tt = localtime(&t[find_number]);
				cout << "���� ��������: " << tt->tm_mday << '/' << (tt->tm_mon + 1) << '/' << (tt->tm_year + 1900) << endl;
				cout << "���������� �������, �� ������� ������ �������: " << period_deposit[find_number] << endl;
			}
			else {
				cout << "������� ��� �� ������" << endl;
			}
		}
		else {
			cout << "�������� �����������" << endl;
		}
	}
	bool withdraw_percent() { //������� �������� � ��������
		if (authorization_status == true) {
			unsigned find_number;
			bool flug = false;
			for (unsigned i = 0; i <= current_position; i++) {
				if (salary_account_recieved == salary_account[i]) {
					find_number = i;
					flug = true;
					break;
				}
			}
			if (flug == true) {
				proc_center.sum_amount(amount_percent[find_number]);
				amount_percent[find_number] = 0;
			}
			else {
				cout << "������� ��� �� ������" << endl;
				return false;
			}
		}
		else {
			cout << "�������� �����������" << endl;
			return false;
		}
		return true;
	}
	bool close_deposit() {
		if (authorization_status == true) {
			unsigned find_number;
			bool flug = false;
			for (unsigned i = 0; i <= current_position; i++) {
				if (salary_account_recieved == salary_account[i]) {
					find_number = i;
					flug = true;
					break;
				}
			}
			if (flug == true) {
				proc_center.sum_amount(amount_deposit[find_number]);
				proc_center.sum_amount(amount_percent[find_number]);
				for (unsigned i = find_number; i < current_position; i++) {
					salary_account[i + 1] = salary_account[i];
					amount_deposit[i + 1] = amount_deposit[i];
					amount_percent[i + 1] = amount_percent[i];
					t[i + 1] = t[i];
					period_deposit[i + 1] = period_deposit[i];
				}
				salary_account[current_position] = "----";
				if (current_position != 0) {
					current_position--;
				}
			}
			else {
				cout << "������� ��� �� ������" << endl;
				return false;
			}
		}
		else {
			cout << "�������� �����������" << endl;
			return false;
		}
		return true;
	}
};

void main() {
	setlocale(LC_ALL, "rus");
	Processing_center A;
	Deposit Ff(A);
	Ff.get_information_about_deposits();
	Ff.authorization("1325", "r4t5e3");
	Ff.get_information_about_deposits();
	cout << Ff.check_deposit() << endl;
	Ff.withdraw_percent();
	Ff.check_status_deposit();
	Ff.close_deposit();
	cout << Ff.check_deposit() << endl;
	Ff.authorization("7685", "0oOoOo0o");
	Ff.authorization("7685", "0o0o0o0o");
	Ff.get_information_about_deposits();
	Ff.open_deposit(5000000, 3);
	Ff.open_deposit(1000000, 7);
	Ff.open_deposit(1000000, 6);
	Ff.check_status_deposit();
	system("pause");
}