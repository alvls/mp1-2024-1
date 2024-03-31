//����������� ����� ��������.
//����� ������ ������� ���������� � ��������� ���������.
//������ ������� �������� ��������� ������ :
//1) �������; 
//2) ���; 
//3) ��������; 
//4) �������; 
//5) ���� ��������(����, �����, ���); 
//6) �������, ��������� �� ������� � ���������.
//�������� �������� ������������ �� �������, �����, ��������.
//�������, ���, ��������(���) �������� ������������� ������.
//������ �������� �� ������� �����.
//����� ������ ��������� ����������� ��������� ������.
//����� ������ ������������� ��������� �������� : 
//1) ������� ����� �������, 
//2) �������� ��������� �������, 
//3) ����� ������� �� ���, 
//4) ����� ������� �� ��������, 
//5) ������ ��� �������� �� �������� �����, 
//6) ������ ������� ����� ���������, 
//7) ������ ������� � ������ ���������, 
//8) ������� ������� �� ������ ���������, 
//9) ������ ��� ��������� ��������, 
//10) ������� �������, 
//11) ��������� �������� � ����, 
//12) ������� �������� �� �����.
#include <iostream> 
#include <string>
#include <ciso646>
#include <clocale>
#include <vector>
#include <algorithm>
#include <fstream>
#include <Windows.h>

using namespace std;

struct birthday
{
	int day;
	int month;
	int year;
};

class Contact
{
	string last_name; 
	string first_name;
	string father_name;
	string phone;
	birthday birth_day;
	bool favorite;
public:
	Contact()
	{
		this->last_name = "������";
		this->first_name = "����";
		this->father_name = "��������";
		this->phone = "�� �������";
		this->birth_day = {0, 0, 0};
		this->favorite = 0;
	}
	Contact(string last_name, string first_name, string father_name, string phone = "�� �������", birthday birth_day = {0, 0, 0}, bool favorite = 0)
	{
		this->last_name = last_name;
		this->first_name = first_name;
		this->father_name = father_name;
		this->phone = phone;
		this->birth_day = birth_day;
		this->favorite = favorite;
	}
	bool operator==(const Contact& rhs)
	{
		if (this->last_name == rhs.last_name and this->first_name == rhs.first_name and this->father_name == rhs.father_name)
			return true;
		else
			return false;
	}
	bool operator!=(const Contact& rhs)
	{
		return !(this->operator==(rhs));
	}
	bool operator<(const Contact& rhs)
	{
		if (*this == rhs)
			return false;
		if (this->last_name != rhs.last_name)
			return (this->last_name < rhs.last_name);
		if (this->first_name != rhs.first_name)
			return (this->first_name < rhs.first_name);
		if (this->father_name != rhs.father_name)
			return (this->father_name < rhs.father_name);
	}
	bool operator>=(const Contact& rhs)
	{
		return !(this->operator<(rhs));
	}
	bool operator>(const Contact& rhs)
	{
		if (*this == rhs)
			return false;
		if (this->last_name != rhs.last_name)
			return (this->last_name > rhs.last_name);
		if (this->first_name != rhs.first_name)
			return (this->first_name > rhs.first_name);
		if (this->father_name != rhs.father_name)
			return (this->father_name > rhs.father_name);
	}
	bool operator<=(const Contact& rhs)
	{
		return !(this->operator>(rhs));
	}
	friend ostream& operator<<(ostream& os, const Contact& rhs)
	{	
		os << rhs.last_name << " " << rhs.first_name << " " << rhs.father_name << endl;
		os << "   �������: ";
		os << rhs.phone << endl;
		os << "   ���� ��������: ";
		if (rhs.birth_day.day == 0)
			os << "�� �������" << endl;
		else
			os << rhs.birth_day.day << "." << rhs.birth_day.month << "." << rhs.birth_day.year << endl;
		if (rhs.favorite)
			os << "   ��������� �������";
		else
			os << "   ������� �������";
		return os;
	}
	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_father_name(const string& father_name)
	{
		this->father_name = father_name;
	}
	void set_phone(const string& phone)
	{
		this->phone = phone;
	}
	void set_birth_day(const birthday& birth_day)
	{
		this->birth_day = birth_day;
	}
	void set_favorite(const bool favorite)
	{
		this->favorite = favorite;
	}
	string get_last_name()
	{
		return this->last_name;
	}
	string get_first_name()
	{
		return this->first_name;
	}
	string get_father_name()
	{
		return this->father_name;
	}
	string get_phone()
	{
		return this->phone;
	}
	birthday get_birth_day()
	{
		return this->birth_day;
	}
	bool get_favorite()
	{
		return this->favorite;
	}
};

class PhoneBook
{
	vector<Contact> contacts;
public:
	PhoneBook(){}

	void add(const Contact& contact)
	{
		contacts.push_back(contact);
		sort(contacts.begin(), contacts.end());
	}
	void add(const string& last_name, const string& first_name, const string& father_name, const string& phone = "�� �������", const birthday& birth_day = { 0, 0, 0 }, const bool& favorite = 0)
	{
		Contact a(last_name, first_name, father_name, phone, birth_day, favorite);
		contacts.push_back(a);
		sort(contacts.begin(), contacts.end());
	}
	void change_last_name(int number, const string& last_name)
	{
		contacts[number - 1].set_last_name(last_name);
		sort(contacts.begin(), contacts.end());
	}
	void change_first_name(int number, const string& first_name)
	{
		contacts[number - 1].set_first_name(first_name);
		sort(contacts.begin(), contacts.end());
	}
	void change_father_name(int number, const string& father_name)
	{
		contacts[number - 1].set_father_name(father_name);
		sort(contacts.begin(), contacts.end());
	}
	void change_phone(int number, const string& phone)
	{
		contacts[number - 1].set_phone(phone);
	}
	void change_birth_day(int number, const birthday& birth_day)
	{
		contacts[number - 1].set_birth_day(birth_day);
	}
	void change_favorite(int number, const bool& favorite)
	{
		contacts[number - 1].set_favorite(favorite);
	}
	void change_contact_fully(int number, const Contact& contact)
	{
		contacts[number - 1] = contact;
		sort(contacts.begin(), contacts.end());
	}
	void change_contact_fully(int number, const string& last_name, const string& first_name, const string& father_name, const string& phone = "�� �������", const birthday& birth_day = { 0, 0, 0 }, const bool& favorite = 0)
	{
		contacts[number - 1].set_last_name(last_name);
		contacts[number - 1].set_first_name(first_name);
		contacts[number - 1].set_father_name(father_name);
		contacts[number - 1].set_phone(phone);
		contacts[number - 1].set_birth_day(birth_day);
		contacts[number - 1].set_favorite(favorite);
		sort(contacts.begin(), contacts.end());
	}
	void find_by_last_name(const string& last_name)
	{	
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_last_name() == last_name)
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� ��������� � �������� " << last_name << endl;
		}
	}
	void find_by_first_name(const string& first_name)
	{
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_first_name() == first_name)
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� ��������� � ������ " << first_name << endl;
		}
	}
	void find_by_father_name(const string& father_name)
	{
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_father_name() == father_name)
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� ��������� � ��������� " << father_name << endl;
		}
	}
	void find_by_first_letter(const char& letter)
	{
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_last_name()[0] == letter)
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� ��������� �� ����� " << letter << endl;
		}
	}
	void find_favorite()
	{
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_favorite())
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� ��������� ���������" << endl;
		}
	}
	void find_by_phone(const string& phone)
	{
		bool flag = false;
		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts[i].get_phone() == phone)
			{
				cout << i + 1 << ". " << contacts[i] << endl;
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "��� �������� � ������� �������� " <<  phone << endl;
		}
	}
	int get_number_of_contacts()
	{
		return contacts.size();
	}
	void delete_contact(int number)
	{
		contacts.erase(contacts.begin() + number - 1);
	}
	friend ostream& operator<<(ostream& os, const PhoneBook Book)
	{	
		os << "\t���������� �����" << endl;
		for (int i = 0; i < Book.contacts.size(); i++)
			os << i + 1 << ". " << Book.contacts[i] << endl;
		os << endl << "����� ���������: ";
		os << Book.contacts.size() << endl;
		return os;
	}
};


int main()
{	
	

	setlocale(LC_ALL, "rus");

	PhoneBook Book;
	

	Contact a("�������", "����", "���������", "+79200373765", { 16, 9, 2004 }, false);
	Contact b("���������", "����", "�������������", "+79307107884", { 8, 1, 2006 }, true);
	Contact c("�������", "�����", "����������");
	Contact d("���������", "���������", "���������");
	Contact e("����������", "�����", "�����������");
	Book.add(a);
	Book.add(b);
	Book.add(c);
	Book.add(d);
	Book.add(e);
	
	
	Book.change_phone(2, "+79407897856");
	Book.change_contact_fully(1, a);
	
	
	Book.change_favorite(1, true);
	cout << Book << endl;
	Book.delete_contact(5);
	cout << Book << endl;
	Book.change_favorite(1, false);
	Book.find_favorite();
	cout << Book.get_number_of_contacts() << endl;
	

	cin.get();
	return 0;

}


