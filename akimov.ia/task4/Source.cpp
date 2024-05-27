#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Contact
{
private:
	string lastName;
	string firstName;
	string middleName;
	string phoneNumber;
	int day;
	int month;
	int year;
	bool isFavorite;
public:
	Contact(string last, string first, string middle, string phone, int d, int m, int y, bool favorite)
	{
		lastName = last;
		firstName = first;
		middleName = middle;
		phoneNumber = phone;
		day = d;
		month = m;
		year = y;
		isFavorite = favorite;
	}
	string getLastName() const { return lastName; }
	string getFirstName() const { return firstName; }
	string getMiddleName() const { return middleName; }
	string getPhone() const { return phoneNumber; }
	int getDay() const { return day; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	bool getIsFavorite() const { return isFavorite; }
    void setLastName(string last) { lastName = last; }
    void setFirstName(string first) { firstName = first; }
    void setMiddleName(string middle) { middleName = middle; }
    void setPhone(string phone) { phoneNumber = phone; }
    void setDay(int d) { day = d; }
    void setMonth(int m) { month = m; }
    void setYear(int y) { year = y; }
	void setIsFavorite(bool favorite) { isFavorite = favorite; }
};

class Contacts
{
private:
	vector<Contact> contacts;
public:
	void addContact(Contact contact)
	{
		contacts.push_back(contact);
		sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b)
			{
				if (a.getLastName() != b.getLastName())
					return a.getLastName() < b.getLastName();
				if (a.getFirstName() != b.getFirstName())
					return a.getFirstName() < b.getFirstName();
				return a.getMiddleName() < b.getMiddleName();
			});
	}

    void changeContact(const string& lastName, const string& firstName, const string& middleName, const string& newPhone, int newDay, int newMonth, int newYear)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setPhone(newPhone);
                contact.setDay(newDay);
                contact.setMonth(newMonth);
                contact.setYear(newYear);
                return;
            }
        throw invalid_argument("������� �� ������");
    }

    Contact findContactByFullName(string lastName, string firstName, string middleName)
    {
        for (const Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
                return contact;
        throw invalid_argument("������� �� ������");
    }

    Contact findContactByPhone(string phone)
    {
        for (const Contact& contact : contacts)
            if (contact.getPhone() == phone)
                return contact;
        throw invalid_argument("������� �� ������");
    }

    vector<Contact> getContactsByLetter(char letter)
    {
        vector<Contact> filteredContacts;
        for (const Contact& contact : contacts)
            if (contact.getLastName().front() == letter)
                filteredContacts.push_back(contact);
        return filteredContacts;
    }

    int getTotalContacts()
    {
        return contacts.size();
    }

    void addFavoriteContact(const string& lastName, const string& firstName, const string& middleName)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setIsFavorite(true);
                return;
            }
        throw invalid_argument("������� �� ������");
    }

    void removeFavoriteContact(const string& lastName, const string& firstName, const string& middleName)
    {
        for (Contact& contact : contacts)
            if (contact.getLastName() == lastName && contact.getFirstName() == firstName && contact.getMiddleName() == middleName)
            {
                contact.setIsFavorite(false);
                return;
            }
        throw invalid_argument("������� �� ������");
    }

    vector<Contact> getFavoriteContacts()
    {
        vector<Contact> favoriteContacts;
        for (const Contact& contact : contacts)
            if (contact.getIsFavorite())
                favoriteContacts.push_back(contact);
        return favoriteContacts;
    }

    void deleteContact(Contact& contact)
    {
        contacts.erase(remove_if(contacts.begin(), contacts.end(), [&contact](const Contact& c) {
            return c.getLastName() == contact.getLastName() && c.getFirstName() == contact.getFirstName() && c.getMiddleName() == contact.getMiddleName(); }), contacts.end());
    }

    void saveContactsToFile(string filename)
    {
        ofstream file;
        file.open(filename);
        if (file.is_open())
        {
            for (const Contact& contact : contacts)
                file << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << " "
                << contact.getPhone() << " " << contact.getDay() << " " << contact.getMonth() << " " << contact.getYear() << " " << contact.getIsFavorite() << endl;
        }
        file.close();
    }   

    void readContactsFromFile(string filename)
    {
        ifstream file(filename);
        if (file.is_open()) 
        {
            string lastName, firstName, middleName, phone;
            int day, month, year;
            bool favorite;
            while (file >> lastName >> firstName >> middleName >> phone >> day >> month >> year >> favorite)
            {
                Contact newContact(lastName, firstName, middleName, phone, day, month, year, favorite);
                addContact(newContact);
            }
        }
        file.close();
    }
};

int main()
{
    system("chcp 1251");
    system("cls");
    Contacts myContacts;
    int choice;
    do {
        cout << "�������� ��������:" << endl;
        cout << "1. ������� ����� �������" << endl;
        cout << "2. �������� ��������� �������" << endl;
        cout << "3. ����� ������� �� ���" << endl;
        cout << "4. ����� ������� �� ��������" << endl;
        cout << "5. �������� ��� �������� �� �������� �����" << endl;
        cout << "6. ������ ������� ����� ���������" << endl;
        cout << "7. �������� ������� � ������ ���������" << endl;
        cout << "8. ������� ������� �� ������ ���������" << endl;
        cout << "9. �������� ��� ��������� ��������" << endl;
        cout << "10. ������� �������" << endl;
        cout << "11. ��������� �������� � ����" << endl;
        cout << "12. ������� �������� �� �����" << endl;
        cout << "0. �����" << endl;
        cout << "�����: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            string lastName, firstName, middleName, phone;
            int day, month, year;
            bool favorite;
            cout << "������� �������: ";
            cin >> lastName;
            cout << "������� ���: ";
            cin >> firstName;
            cout << "������� ��������: ";
            cin >> middleName;
            cout << "������� �������: ";
            cin >> phone;
            cout << "������� ���� �������� (���� ����� ���): ";
            cin >> day >> month >> year;
            cout << "�������� ���� ������� � ��������� (0 - ���, 1 - ��): ";
            cin >> favorite;
            Contact newContact(lastName, firstName, middleName, phone, day, month, year, favorite);
            myContacts.addContact(newContact);
            system("cls");
            cout << "������� ������� ��������" << endl << endl;
            break;
        }
        case 2:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "������� ������� ������� ��������: ";
            cin >> lastName;
            cout << "������� ��� ������� ��������: ";
            cin >> firstName;
            cout << "������� �������� ������� ��������: ";
            cin >> middleName;
            try
            {
                myContacts.findContactByFullName(lastName, firstName, middleName);
                string newPhone;
                int newDay, newMonth, newYear;
                cout << "������� ����� �������: ";
                cin >> newPhone;
                cout << "������� ����� ���� �������� (���� ����� ���): ";
                cin >> newDay >> newMonth >> newYear;
                myContacts.changeContact(lastName, firstName, middleName, newPhone, newDay, newMonth, newYear);
                system("cls");
                cout << "������� ������� �������" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 3:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "������� ������� ������� ��������: ";
            cin >> lastName;
            cout << "������� ��� ������� ��������: ";
            cin >> firstName;
            cout << "������� �������� ������� ��������: ";
            cin >> middleName;
            try
            {
                system("cls");
                Contact foundContact = myContacts.findContactByFullName(lastName, firstName, middleName);
                cout << "������ �������:" << endl;
                cout << "�������: " << foundContact.getLastName() << endl;
                cout << "���: " << foundContact.getFirstName() << endl;
                cout << "��������: " << foundContact.getMiddleName() << endl;
                cout << "�������: " << foundContact.getPhone() << endl;
                cout << "���� ��������: " << foundContact.getDay() << "." << foundContact.getMonth() << "." << foundContact.getYear() << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 4:
        {
            system("cls");
            string phone;
            cout << "������� ������� ������� ��������: ";
            cin >> phone;
            try
            {
                system("cls");
                Contact foundContact = myContacts.findContactByPhone(phone);
                cout << "������ �������:" << endl;
                cout << "�������: " << foundContact.getLastName() << endl;
                cout << "���: " << foundContact.getFirstName() << endl;
                cout << "��������: " << foundContact.getMiddleName() << endl;
                cout << "�������: " << foundContact.getPhone() << endl;
                cout << "���� ��������: " << foundContact.getDay() << "." << foundContact.getMonth() << "." << foundContact.getYear() << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 5:
        {
            system("cls");
            char letter;
            cout << "������� �����: ";
            cin >> letter;
            vector<Contact> contactsByLetter = myContacts.getContactsByLetter(letter);
            if (contactsByLetter.empty())
            {
                system("cls");
                cout << "��������� �� �������� ����� �� �������" << endl << endl;
            }
            else
            {
                system("cls");
                cout << "�������� �� ����� '" << letter << "':" << endl;
                for (const Contact& contact : contactsByLetter)
                    cout << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << endl;
                cout << endl;
            }
            break;
        }
        case 6:
            system("cls");
            cout << "������� ���� ���������:" << myContacts.getTotalContacts() << endl << endl;
            break;
        case 7:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "������� ������� ������� ��������: ";
            cin >> lastName;
            cout << "������� ��� ������� ��������: ";
            cin >> firstName;
            cout << "������� �������� ������� ��������: ";
            cin >> middleName;
            try
            {
                myContacts.addFavoriteContact(lastName, firstName, middleName);
                system("cls");
                cout << "������� ������� �������� � ������ ���������" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 8:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "������� ������� ������� ��������: ";
            cin >> lastName;
            cout << "������� ��� ������� ��������: ";
            cin >> firstName;
            cout << "������� �������� ������� ��������: ";
            cin >> middleName;
            try
            {
                myContacts.removeFavoriteContact(lastName, firstName, middleName);
                system("cls");
                cout << "������� ������� ������ �� ������ ���������" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 9:
        {
            system("cls");
            vector<Contact> favoriteContacts = myContacts.getFavoriteContacts();
            if (favoriteContacts.empty())
                cout << "��� ��������� ���������" << endl << endl;
            else
            {
                cout << "��������� ��������:" << endl;
                for (const Contact& contact : favoriteContacts)
                    cout << contact.getLastName() << " " << contact.getFirstName() << " " << contact.getMiddleName() << endl;
                cout << endl;
            }
            break;
        }
        case 10:
        {
            system("cls");
            string lastName, firstName, middleName;
            cout << "������� ������� ������� ��������: ";
            cin >> lastName;
            cout << "������� ��� ������� ��������: ";
            cin >> firstName;
            cout << "������� �������� ������� ��������: ";
            cin >> middleName;
            try
            {
                Contact contactToDelete = myContacts.findContactByFullName(lastName, firstName, middleName);
                myContacts.deleteContact(contactToDelete);
                system("cls");
                cout << "������� ������� ������" << endl << endl;
            }
            catch (...)
            {
                system("cls");
                cout << "������� �� ������" << endl << endl;
            }
            break;
        }
        case 11:
        {
            system("cls");
            string path;
            cout << "������� ���� � ����� ��� ���������� ���������: ";
            cin.ignore();
            getline(cin, path);
            myContacts.saveContactsToFile(path);
            system("cls");
            cout << "�������� ������� ��������� � " << path << endl << endl;
            break;
        }
        case 12:
        {
            system("cls");
            string path;
            cout << "������� ���� � ����� ��� ���������� ���������: ";
            cin.ignore();
            getline(cin, path);
            myContacts.readContactsFromFile(path);
            system("cls");
            cout << "�������� ������� ������� �� " << path << endl << endl;
            break;
        }
        case 0:
            system("cls");
            cout << "����� �� ���������" << endl << endl;
            break;
        default:
            system("cls");
            cout << "������������ ����" << endl << endl;
        }
    } while (choice != 0);
    system("pause");
    return 0;
}